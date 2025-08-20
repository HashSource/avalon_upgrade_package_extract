# Avalon Upgrade Package (AUP) File Format

This document details the structure and contents of the Avalon Upgrade Package (AUP) file format used for distributing firmware updates for Canaan Avalon miners. Information is derived from the `fms-core` library, specifically the `fmsc/aupparser.py` and `fmsc/aupfile.py` modules.

## Overall Structure

An AUP file is a binary file consisting of two main parts:

1.  **Header:** Contains metadata about the firmware, including version information, payload details, compatibility information, and integrity checks. The exact structure of the header depends on its format version (`fmt_ver`).
2.  **Payload:** Contains the actual raw firmware binary data to be flashed onto the miner.

```
+-------------------+
| Header            |
| (Variable Format) |
+-------------------+
| Payload           |
| (Firmware Binary) |
+-------------------+
```

## Header Details

All AUP headers start with the same 16-byte magic string and a 4-byte format version identifier.

```
struct AupCommonHeader {
    char magic[16];      // Always "AUP format\0" (null-terminated)
    uint32_t fmt_ver;    // Header format version (0, 1, or 2)
};
```

The value of `fmt_ver` determines the structure of the subsequent header fields.

### Header Format Version 0 (`fmt_ver == 0`)

This is the simplest and earliest known header format.

**Structure:**

```c
// Following AupCommonHeader
struct Aup0_Data {
    uint32_t payload_len;    // Length of the firmware payload in bytes
    char firmware_ver[64]; // Firmware version string (null-terminated)
    uint32_t payload_crc;    // CRC32 checksum of the payload section
};
```

- **Total Header Size:** 92 bytes (16 + 4 + 4 + 64 + 4).
- **Fields:**
  - `payload_len`: Size of the firmware data following the header.
  - `firmware_ver`: A human-readable string identifying the firmware version (e.g., "19101501_f293f38_2fbfeda"). Padded with null bytes.
  - `payload_crc`: CRC32 checksum calculated over the entire payload section.

### Header Format Version 1 (`fmt_ver == 1`)

This version adds a list of compatible hardware types.

**Structure:**

```c
// Following AupCommonHeader
struct Aup1_Data {
    uint32_t header_len;      // Total length of this AUP header (Seems to be 224?)
    char hw_list_str[128]; // Comma-separated list of compatible hardware types (null-terminated string)
    uint32_t payload_len;     // Length of the firmware payload in bytes
    char firmware_ver[64];  // Firmware version string (null-terminated)
    uint32_t payload_crc;     // CRC32 checksum of the payload section
};
```

- **Total Header Size:** 224 bytes (16 + 4 + 4 + 128 + 4 + 64 + 4).
- **Fields:**
  - `header_len`: Specifies the size of this header structure.
  - `hw_list_str`: A single string containing comma-separated hardware type identifiers (e.g., "MM3v1_X3,MM5v1"). Padded with null bytes.
  - `payload_len`, `firmware_ver`, `payload_crc`: Same meaning as in Version 0.

### Header Format Version 2 (`fmt_ver == 2`)

This version introduces separate lists for hardware and software types and adds a CRC check for the header itself.

**Structure:**

```c
// Following AupCommonHeader
struct Fixed32Str {
    char str_value[32]; // Null-terminated string, padded with nulls
};

struct Aup2_Data {
    uint32_t payload_len;     // Length of the firmware payload in bytes
    char firmware_ver[64];  // Firmware version string (null-terminated)
    uint32_t payload_crc;     // CRC32 checksum of the payload section
    uint32_t hw_list_count;   // Number of entries in hw_list
    uint32_t sw_list_count;   // Number of entries in sw_list
    Fixed32Str hw_list[];     // Array of hw_list_count compatible hardware types
    Fixed32Str sw_list[];     // Array of sw_list_count compatible software types
    // uint32_t header_crc; // CRC32 checksum of the header *before* this field
};
// Note: The header_crc field follows immediately after sw_list data.
```

- **Total Header Size:** Variable. Calculated as: `100 + (hw_list_count * 32) + (sw_list_count * 32) + 4` bytes.
  - 100 bytes = Common Header (20) + fixed fields in `Aup2_Data` (4 + 64 + 4 + 4 + 4).
  - `hw_list_count * 32`: Size of the hardware list data.
  - `sw_list_count * 32`: Size of the software list data.
  - 4 bytes: Size of the final `header_crc`.
- **Fields:**
  - `payload_len`, `firmware_ver`, `payload_crc`: Same meaning as in previous versions.
  - `hw_list_count`: Number of hardware type strings in the `hw_list`.
  - `sw_list_count`: Number of software type strings in the `sw_list`.
  - `hw_list`: An array of fixed-size (32 bytes) null-terminated strings, each specifying a compatible hardware type (e.g., "MM3v1_X3").
  - `sw_list`: An array of fixed-size (32 bytes) null-terminated strings, each specifying a compatible software type (e.g., "MM310").
  - `header_crc`: A CRC32 checksum calculated over all preceding bytes of the header (from the start of the `magic` field up to, but not including, the `header_crc` field itself).

## Payload

The payload section begins immediately after the header ends. It contains the raw binary data of the firmware image.

- **Length:** The exact size is specified by the `payload_len` field in the header.
- **Content:** Opaque firmware data.
- **Integrity:** Verified using the `payload_crc` (CRC32) value stored in the header.

## Checks and Validation

The `fms-core` library (and presumably the miner firmware) performs several checks to validate an AUP file before proceeding with an upgrade:

1.  **Magic String:** Verifies the first 16 bytes match `"AUP format\0"`.
2.  **Header CRC (Version 2 only):** Calculates the CRC32 of the header (excluding the CRC field itself) and compares it against the stored `header_crc`.
3.  **Payload CRC:** Calculates the CRC32 of the entire payload section and compares it against the stored `payload_crc`.
4.  **Hardware/Software Compatibility:** The `hw_list` and `sw_list` (if present in the header format) are compared against the hardware/software type reported by the target miner via its API. An upgrade is typically prevented if there's a mismatch. (See `fmsc.aioupgrade.aio_mm3_upgrade_precheck`).

## Header Version Compatibility

The upgrade process needs to handle different AUP header versions. The `fms-core` library includes logic (`fmsc.aupfile.generate_aup_header_payload`, used in `fmsc.aioupgrade._hack_aup_header_when_cross_aup_header_ver_upgrade`) to potentially generate a compatible header (e.g., generating a Version 0 or Version 2 header from an existing AUP file's data) when communicating with miners that expect a specific format based on their current firmware or API version. This ensures older miners can receive firmware packaged in newer AUP formats and vice-versa, where applicable.
