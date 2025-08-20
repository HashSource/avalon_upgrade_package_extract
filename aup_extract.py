#!/usr/bin/env python3

"""
Avalon Upgrade Package (AUP) Parser

This module provides functionality to parse Avalon firmware upgrade package files.
It supports multiple versions of the AUP format (v0, v1, and v2) and can extract
payload data for further processing.

The AUP format consists of:
- A header containing metadata (magic string, version, firmware info)
- Hardware and software compatibility information
- A payload containing the actual firmware data
- CRC checksums for validation
"""

import binascii
import logging
import struct
from dataclasses import dataclass, field
from io import BytesIO
from pathlib import Path
from typing import Dict, List, Optional

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


@dataclass
class AUPParseResult:
    """
    Data class to store parsing results for an AUP file.

    Attributes:
        filename: Name of the parsed file
        is_valid: Whether the file was successfully parsed and validated
        magic: Magic string from the header ("AUP format")
        version: AUP format version (0, 1, or 2)
        firmware_version: Version string of the firmware
        payload_length: Size of the firmware payload in bytes
        payload_crc: CRC32 checksum of the payload
        header_size: Total size of the header in bytes
        payload: Raw firmware payload bytes
        hardware_types: List of compatible hardware models
        software_types: List of compatible software versions
        error_message: Description of any error that occurred during parsing
    """

    filename: str
    is_valid: bool
    magic: str = ""
    version: int = 0
    firmware_version: str = ""
    payload_length: int = 0
    payload_crc: int = 0
    header_size: int = 0
    payload: bytes = None
    hardware_types: List[str] = field(default_factory=list)
    software_types: List[str] = field(default_factory=list)
    error_message: str = ""

    def verify_payload_crc(self) -> bool:
        """Verify the payload CRC matches the stored CRC value."""
        if not self.payload:
            return False
        return (binascii.crc32(self.payload) & 0xFFFFFFFF) == self.payload_crc


class AUPParser:
    """
    Parser for Avalon Upgrade Package (AUP) files.

    Supports three versions of the AUP format:
    - Version 0: Basic format with firmware and CRC
    - Version 1: Adds hardware compatibility list (comma-separated)
    - Version 2: Adds software compatibility list and structured HW/SW lists
    """

    # File format constants
    MAGIC_STRING = b"AUP format"
    HEADER_SIZES = {
        0: 92,  # 16 (magic) + 4 (version) + 4 (payload_len) + 64 (firmware_ver) + 4 (crc)
        1: 224,  # v0 size + 4 (header_len) + 128 (hw_list) + additional fields
    }
    HEADER_MAGIC_SIZE = 16  # Size of magic string field
    VERSION_SIZE = 4  # Size of version field
    FIRMWARE_VER_SIZE = 64  # Size of firmware version string
    FIXED_STR_SIZE = 32  # Size of fixed-length strings in v2 format

    def __init__(self):
        """Initialize parser with empty results dictionary."""
        self.results: Dict[str, AUPParseResult] = {}

    def parse_directory(
        self, directory_path: Path, extract_path: Optional[Path] = None
    ) -> Dict[str, AUPParseResult]:
        """
        Parse all .aup files in the specified directory.

        Args:
            directory_path: Path to directory containing .aup files
            extract_path: Optional path to extract payloads to

        Returns:
            Dictionary mapping filenames to their parse results

        Raises:
            ValueError: If directory_path is not a valid directory
        """
        directory_path = Path(directory_path)
        if not directory_path.is_dir():
            raise ValueError(f"'{directory_path}' is not a valid directory")

        if extract_path:
            extract_path = Path(extract_path)
            extract_path.mkdir(parents=True, exist_ok=True)

        for file_path in directory_path.glob("*.aup"):
            try:
                result = self.parse_file(file_path)
                self.results[file_path.name] = result

                if extract_path and result.is_valid and result.payload:
                    self._extract_payload(result, extract_path)
            except Exception as e:
                logger.error(f"Error parsing {file_path}: {e}")
                self.results[file_path.name] = AUPParseResult(
                    filename=file_path.name,
                    is_valid=False,
                    error_message=f"Parse error: {e}",
                )

        return self.results

    def _extract_payload(self, result: AUPParseResult, extract_path: Path) -> None:
        """
        Extract payload to a binary file.

        Args:
            result: Parse result containing the payload
            extract_path: Directory to save the extracted payload
        """
        try:
            output_path = extract_path / f"{Path(result.filename).stem}_payload.bin"
            output_path.write_bytes(result.payload)
            logger.info(f"Extracted payload to: {output_path}")
        except Exception as e:
            logger.error(f"Failed to extract payload: {e}")

    def get_header_size(
        self, version: int, hw_count: int = 0, sw_count: int = 0
    ) -> int:
        """
        Calculate total header size based on AUP version and content.

        Args:
            version: AUP format version
            hw_count: Number of hardware type entries (v2 only)
            sw_count: Number of software type entries (v2 only)

        Returns:
            Total size of the header in bytes

        Raises:
            ValueError: If version is not supported
        """
        if version in self.HEADER_SIZES:
            return self.HEADER_SIZES[version]
        if version == 2:
            # v2 header: base size + fixed-length strings for HW/SW + CRC
            return 100 + self.FIXED_STR_SIZE * (hw_count + sw_count) + 4
        raise ValueError(f"Unsupported version: {version}")

    def parse_file(self, file_path: Path) -> AUPParseResult:
        """
        Parse a single AUP file.

        The parsing process:
        1. Validates the magic string
        2. Determines the format version
        3. Parses version-specific header information
        4. Extracts and validates the payload

        Args:
            file_path: Path to the AUP file

        Returns:
            AUPParseResult containing the parsed information
        """
        file_path = Path(file_path)
        result = AUPParseResult(filename=file_path.name, is_valid=False)

        try:
            file_content = file_path.read_bytes()

            # Validate magic string and version
            if not file_content.startswith(self.MAGIC_STRING):
                result.error_message = "Invalid magic string"
                return result

            result.magic = file_content[: self.HEADER_MAGIC_SIZE].decode().strip("\0")
            result.version = struct.unpack(
                "<I",
                file_content[
                    self.HEADER_MAGIC_SIZE : self.HEADER_MAGIC_SIZE + self.VERSION_SIZE
                ],
            )[0]

            # Parse header according to version
            f = BytesIO(file_content[self.HEADER_MAGIC_SIZE + self.VERSION_SIZE :])
            parser = getattr(self, f"_parse_v{result.version}", None)
            if not parser:
                result.error_message = f"Unsupported version: {result.version}"
                return result

            parser(f, result)

            # Calculate header size and extract payload
            result.header_size = self.get_header_size(
                result.version, len(result.hardware_types), len(result.software_types)
            )

            result.payload = file_content[
                result.header_size : result.header_size + result.payload_length
            ]

            # Verify payload size and CRC
            if len(result.payload) != result.payload_length:
                result.error_message = f"Payload size mismatch. Expected: {result.payload_length}, Got: {len(result.payload)}"
                return result

            if not result.verify_payload_crc():
                result.error_message = "Payload CRC verification failed"
                return result

            result.is_valid = True
            return result

        except Exception as e:
            result.error_message = f"Parse error: {e}"
            return result

    def _parse_v0(self, f: BytesIO, result: AUPParseResult) -> None:
        """
        Parse version 0 AUP format.

        Basic format with:
        - Payload length (4 bytes)
        - Firmware version (64 bytes)
        - Payload CRC (4 bytes)
        """
        result.payload_length = struct.unpack("<I", f.read(4))[0]
        result.firmware_version = f.read(self.FIRMWARE_VER_SIZE).decode().strip("\0")
        result.payload_crc = struct.unpack("<I", f.read(4))[0]

    def _parse_v1(self, f: BytesIO, result: AUPParseResult) -> None:
        """
        Parse version 1 AUP format.

        Adds to v0:
        - Header length (4 bytes)
        - Hardware compatibility list (128 bytes, comma-separated)
        """
        _ = struct.unpack("<I", f.read(4))[0]  # header_len

        hw_list_raw = f.read(128)
        result.hardware_types = [
            hw.decode().strip("\0") for hw in hw_list_raw.split(b",") if hw
        ]

        result.payload_length = struct.unpack("<I", f.read(4))[0]
        result.firmware_version = f.read(self.FIRMWARE_VER_SIZE).decode().strip("\0")
        result.payload_crc = struct.unpack("<I", f.read(4))[0]

    def _parse_v2(self, f: BytesIO, result: AUPParseResult) -> None:
        """
        Parse version 2 AUP format.

        Adds to v1:
        - Software compatibility list
        - Structured format for HW/SW lists using fixed-length strings
        """
        result.payload_length = struct.unpack("<I", f.read(4))[0]
        result.firmware_version = f.read(self.FIRMWARE_VER_SIZE).decode().strip("\0")
        result.payload_crc = struct.unpack("<I", f.read(4))[0]

        hw_count, sw_count = struct.unpack("<II", f.read(8))

        # Read fixed-length hardware type strings
        result.hardware_types = [
            f.read(self.FIXED_STR_SIZE).decode().strip("\0") for _ in range(hw_count)
        ]
        result.hardware_types = [hw for hw in result.hardware_types if hw]

        # Read fixed-length software type strings
        result.software_types = [
            f.read(self.FIXED_STR_SIZE).decode().strip("\0") for _ in range(sw_count)
        ]
        result.software_types = [sw for sw in result.software_types if sw]


def main():
    """Command-line interface for the AUP parser."""
    import argparse

    parser = argparse.ArgumentParser(
        description="Parse Avalon Upgrade Package (AUP) files"
    )
    parser.add_argument("directory", type=Path, help="Directory containing .aup files")
    parser.add_argument(
        "--extract", "-e", type=Path, help="Directory to extract payloads to"
    )
    parser.add_argument(
        "--verbose", "-v", action="store_true", help="Enable verbose output"
    )
    args = parser.parse_args()

    if args.verbose:
        logging.getLogger().setLevel(logging.DEBUG)

    try:
        results = AUPParser().parse_directory(args.directory, args.extract)

        print("\nParsing Results:")
        print("===============")

        for filename, result in results.items():
            print(f"\nFile: {filename}")
            print(f"Valid: {result.is_valid}")

            if result.is_valid:
                print(f"Version: {result.version}")
                print(f"Firmware Version: {result.firmware_version}")
                print(f"Payload Length: {result.payload_length}")
                print(f"Payload CRC: {result.payload_crc:08x}")
                print(f"Header Size: {result.header_size}")

                if result.hardware_types:
                    print(f"Hardware Types: {', '.join(result.hardware_types)}")
                if result.software_types:
                    print(f"Software Types: {', '.join(result.software_types)}")

                print(f"Payload CRC Valid: {result.verify_payload_crc()}")
            else:
                print(f"Error: {result.error_message}")

    except Exception as e:
        logger.error(f"Error: {e}")
        return 1

    return 0


if __name__ == "__main__":
    exit(main())
