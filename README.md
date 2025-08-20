# Avalon Upgrade Package (AUP) Extract Tool

A Python utility for parsing and extracting firmware payloads from Avalon miner upgrade packages (.aup files).

## Overview

This tool analyzes Avalon Upgrade Package (AUP) files used for firmware distribution on Canaan Avalon Bitcoin mining hardware. It supports multiple AUP format versions (v0, v1, v2) and can extract firmware payloads for analysis.

## Features

- Parse AUP file headers to extract metadata
- Support for all AUP format versions (0, 1, 2)
- Extract firmware payloads from AUP packages
- Verify payload integrity via CRC32 checksums
- Batch processing of multiple AUP files
- Hardware/software compatibility information extraction

## Directory Structure

```
├── aup_extract.py          # Main extraction script
├── aup_extract.sh          # Batch extraction wrapper
├── AUP_FORMAT.md           # Detailed AUP format specification
├── aup_files/              # Input AUP files
├── aup_files_payloads/     # Extracted firmware payloads
├── fmsc/                   # Core parsing library from fms-core
└── AvalonNano3_Upgrade/    # C implementation reference files
```

## Usage

### Single Directory Processing

```bash
python aup_extract.py <directory> [--extract <output_dir>] [--verbose]
```

### Batch Extraction

```bash
./aup_extract.sh
```

This will process all AUP files in `aup_files/` and extract payloads to `aup_files_payloads/`.

## AUP File Format

AUP files consist of:
- **Header**: Contains metadata, version info, and compatibility lists
- **Payload**: Raw firmware binary data

See [AUP_FORMAT.md](AUP_FORMAT.md) for detailed format specifications.

## Requirements

- Python 3.6+
- Standard library only (no external dependencies)

## Output

The tool displays:
- File validation status
- Format version
- Firmware version string
- Payload size and CRC
- Compatible hardware/software types
- CRC verification results

## License

Components from fms-core are licensed under Apache License 2.0.