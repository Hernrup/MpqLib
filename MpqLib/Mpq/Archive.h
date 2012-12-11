//+-----------------------------------------------------------------------------
//|
//| Copyright (C) 2008, Magnus Ostberg, aka Magos
//| Contact: MagosX@GMail.com, http://www.magosx.com
//|
//| This file is part of MpqLib.
//| MpqLib is a library to manipulate (open, read, write) MoPaQ archives and
//| its contained files for the game WarCraft 3. It can (and is supposed to)
//| be freely used in tools and programs made by other developers.
//|
//| WarCraft is a trademark of Blizzard Entertainment, Inc.
//|
//| MpqLib is free software: you can redistribute it and/or modify
//| it under the terms of the GNU General Public License as published by
//| the Free Software Foundation, either version 3 of the License, or
//| (at your option) any later version.
//|
//| MpqLib is distributed in the hope that it will be useful,
//| but WITHOUT ANY WARRANTY; without even the implied warranty of
//| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//| GNU General Public License for more details.
//|
//| You should have received a copy of the GNU General Public License
//| along with MpqLib. If not, see <http://www.gnu.org/licenses/>.
//|
//| This header must remain unaltered if changes are made to the file.
//| Additional information may be added as needed.
//|
//+-----------------------------------------------------------------------------
#pragma once

#include "FileInfo.h"
#include "StringHandle.h"
#include "TemporaryFile.h"
#include "Quality.h"
#include "Compression.h"
#include "Encryption.h"
#include "ArchiveFormat.h"

namespace MpqLib
{
	namespace Mpq
	{
		/// <summary>
		/// Represents an MPQ archive which contains a number of files.
		/// Files can be imported/exported.
		/// </summary>
		public ref class CArchive sealed
		{
			public:
				/// <summary>
				/// Parameterized constructor.
				/// </summary>
				/// <param name="FileName">The archive to open</param>
				CArchive(System::String^ FileName);

				/// <summary>
				/// Parameterized constructor.
				/// </summary>
				/// <param name="FileName">The archive to open or create</param>
				/// <param name="CreateIfNotExists">Decides if a new archive should be created if none exists</param>
				CArchive(System::String^ FileName, System::Boolean CreateIfNotExists);

				/// <summary>
				/// Parameterized constructor.
				/// </summary>
				/// <param name="FileName">The archive to open or create</param>
				/// <param name="CreateIfNotExists">Decides if a new archive should be created if none exists</param>
				/// <param name="ArchiveFormat">Which MPQ format to use (higher version supports larger files)</param>
				CArchive(System::String^ FileName, System::Boolean CreateIfNotExists, EArchiveFormat ArchiveFormat);

				/// <summary>
				/// Parameterized constructor.
				/// </summary>
				/// <param name="FileName">The archive to open or create</param>
				/// <param name="CreateIfNotExists">Decides if a new archive should be created if none exists</param>
				/// <param name="ArchiveFormat">Which MPQ format to use (higher version supports larger files)</param>
				/// <param name="HashTableSize">The initial size of the hashtable</param>
				CArchive(System::String^ FileName, System::Boolean CreateIfNotExists, EArchiveFormat ArchiveFormat, System::UInt32 HashTableSize);

				/// <summary>
				/// Releases all resources used by the MpqLib.Mpq.CArchive.
				/// </summary>
				~CArchive();

				/// <summary>
				/// Releases all resources used by the MpqLib.Mpq.CArchive.
				/// </summary>
				!CArchive();

				/// <summary>
				/// Closes the archive.
				/// </summary>
				System::Void Close();

				/// <summary>
				/// Flushes the archive, committing unsaved changes.
				/// </summary>
				System::Void Flush();

				/// <summary>
				/// Compacts the archive, potentially reducing its size.
				/// </summary>
				System::Void Compact();

				/// <summary>
				/// Checks if a file exists in the archive.
				/// </summary>
				/// <param name="FileName">The file to check</param>
				/// <returns>True if the file exists, False otherwise</returns>
				System::Boolean FileExists(System::String^ FileName);

				/// <summary>
				/// Imports a file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="RealFileName">The file to import</param>
				System::Void ImportFile(System::String^ FileName, System::String^ RealFileName);

				/// <summary>
				/// Imports a file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="RealFileName">The file to import</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				System::Void ImportFile(System::String^ FileName, System::String^ RealFileName, ECompression Compression);

				/// <summary>
				/// Imports a file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="RealFileName">The file to import</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				/// <param name="Encryption">Which encryption to use on the file when importing</param>
				System::Void ImportFile(System::String^ FileName, System::String^ RealFileName, ECompression Compression, EEncryption Encryption);

				/// <summary>
				/// Imports a file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="FileData">The file to import, stored in a buffer</param>
				System::Void ImportFile(System::String^ FileName, array<System::Byte>^ FileData);

				/// <summary>
				/// Imports a file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="FileData">The file to import, stored in a buffer</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				System::Void ImportFile(System::String^ FileName, array<System::Byte>^ FileData, ECompression Compression);

				/// <summary>
				/// Imports a file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="FileData">The file to import, stored in a buffer</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				/// <param name="Encryption">Which encryption to use on the file when importing</param>
				System::Void ImportFile(System::String^ FileName, array<System::Byte>^ FileData, ECompression Compression, EEncryption Encryption);

				/// <summary>
				/// Imports a wave file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="RealFileName">The file to import</param>
				/// <param name="Quality">Which quality to use on the file when importing</param>
				System::Void ImportWaveFile(System::String^ FileName, System::String^ RealFileName, EQuality Quality);

				/// <summary>
				/// Imports a wave file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="RealFileName">The file to import</param>
				/// <param name="Quality">Which quality to use on the file when importing</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				System::Void ImportWaveFile(System::String^ FileName, System::String^ RealFileName, EQuality Quality, ECompression Compression);

				/// <summary>
				/// Imports a wave file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="RealFileName">The file to import</param>
				/// <param name="Quality">Which quality to use on the file when importing</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				/// <param name="Encryption">Which encryption to use on the file when importing</param>
				System::Void ImportWaveFile(System::String^ FileName, System::String^ RealFileName, EQuality Quality, ECompression Compression, EEncryption Encryption);

				/// <summary>
				/// Imports a wave file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="FileData">The file to import, stored in a buffer</param>
				/// <param name="Quality">Which quality to use on the file when importing</param>
				System::Void ImportWaveFile(System::String^ FileName, array<System::Byte>^ FileData, EQuality Quality);

				/// <summary>
				/// Imports a wave file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="FileData">The file to import, stored in a buffer</param>
				/// <param name="Quality">Which quality to use on the file when importing</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				System::Void ImportWaveFile(System::String^ FileName, array<System::Byte>^ FileData, EQuality Quality, ECompression Compression);

				/// <summary>
				/// Imports a wave file to the archive.
				/// </summary>
				/// <param name="FileName">The filename to save as in the archive</param>
				/// <param name="FileData">The file to import, stored in a buffer</param>
				/// <param name="Quality">Which quality to use on the file when importing</param>
				/// <param name="Compression">Which compression to use on the file when importing</param>
				/// <param name="Encryption">Which encryption to use on the file when importing</param>
				System::Void ImportWaveFile(System::String^ FileName, array<System::Byte>^ FileData, EQuality Quality, ECompression Compression, EEncryption Encryption);

				/// <summary>
				/// Imports a listfile to the archive, merging it with existing listfiles.
				/// </summary>
				/// <param name="FileName">The listfile to import</param>
				System::Void ImportListFile(System::String^ FileName);

				/// <summary>
				/// Imports a listfile to the archive, merging it with existing listfiles.
				/// </summary>
				/// <param name="FileData">The listfile to import, stored in a buffer</param>
				System::Void ImportListFile(array<System::Byte>^ FileData);

				/// <summary>
				/// Exports a file from the archive, saving it to a physical file.
				/// </summary>
				/// <param name="FileName">The file to export</param>
				/// <param name="RealFileName">The physical file to save to</param>
				System::Void ExportFile(System::String^ FileName, System::String^ RealFileName);

				/// <summary>
				/// Exports a file from the archive, saving it to a buffer.
				/// </summary>
				/// <param name="FileName">The file to export</param>
				/// <param name="FileData">The buffer to save to</param>
				System::Void ExportFile(System::String^ FileName, array<System::Byte>^ FileData);

				/// <summary>
				/// Exports a file from the archive, saving it to a buffer.
				/// </summary>
				/// <param name="FileName">The file to export</param>
				/// <param name="FileData">The buffer to save to</param>
				/// <param name="Index">The index in the buffer to start writing at</param>
				System::Void ExportFile(System::String^ FileName, array<System::Byte>^ FileData, System::Int32 Index);

				/// <summary>
				/// Renames a file in the archive.
				/// </summary>
				/// <param name="FileName">The file to rename</param>
				/// <param name="NewFileName">the new name for the file</param>
				System::Void RenameFile(System::String^ FileName, System::String^ NewFileName);

				/// <summary>
				/// Removes a file from the archive.
				/// </summary>
				/// <param name="FileName">The file to remove</param>
				System::Void RemoveFile(System::String^ FileName);

				/// <summary>
				/// Retrieves information about the files in the archive.
				/// </summary>
				/// <param name="Mask">A wildcard filter deciding which files to include in the search</param>
				/// <returns>A collection of the files found</returns>
				System::Collections::Generic::IEnumerable<CFileInfo^>^ FindFiles(System::String^ Mask);

				/// <summary>
				/// Retrieves information about the files in the archive, only relying on the listfile.
				/// </summary>
				/// <param name="Mask">A wildcard filter deciding which files to include in the search</param>
				/// <param name="TraverseListFileOnly">Decides whether to only rely on the files in the listfile or not</param>
				/// <returns>A collection of the files found</returns>
				System::Collections::Generic::IEnumerable<CFileInfo^>^ FindFiles(System::String^ Mask, System::Boolean TraverseListFileOnly);

				/// <summary>
				/// Retrieves information about the files in the archive. Uses an external listfile instead of an included one.
				/// </summary>
				/// <param name="Mask">A wildcard filter deciding which files to include in the search</param>
				/// <param name="ExternalListFile">A path to an external listfile to use</param>
				/// <returns>A collection of the files found</returns>
				System::Collections::Generic::IEnumerable<CFileInfo^>^ FindFiles(System::String^ Mask, System::String^ ExternalListFile);

				/// <summary>
				/// Retrieves information about the files in the archive, only relying on the listfile. Uses an external listfile instead of an included one.
				/// </summary>
				/// <param name="Mask">A wildcard filter deciding which files to include in the search</param>
				/// <param name="ExternalListFile">A path to an external listfile to use</param>
				/// <param name="TraverseListFileOnly">Decides whether to only rely on the files in the listfile or not</param>
				/// <returns>A collection of the files found</returns>
				System::Collections::Generic::IEnumerable<CFileInfo^>^ FindFiles(System::String^ Mask, System::String^ ExternalListFile, System::Boolean TraverseListFileOnly);

				/// <summary>
				/// Generates a string version of the archive.
				/// </summary>
				/// <returns>The generated string</returns>
				virtual System::String^ ToString() override;

				/// <summary>
				/// Retrieves the number of files in the archive.
				/// </summary>
				property System::Int32 FileCount { System::Int32 get(); }

				/// <summary>
				/// Gets or sets the archive locale (for language specific files).
				/// </summary>
				property LCID Locale { LCID get(); System::Void set(LCID Locale); }

				/// <summary>
				/// Retrieves the archive handle.
				/// </summary>
				property HANDLE Handle { HANDLE get(); }

				/// <summary>
				/// Retrieves the archive filename.
				/// </summary>
				property System::String^ FileName { System::String^ get(); }

				/// <summary>
				/// Gets or sets the tag data of the archive.
				/// </summary>
				property System::Object^ Tag { System::Object^ get(); System::Void set(System::Object^ Tag); }

				/// <summary>
				/// Checks if the archive has been disposed.
				/// </summary>
				property System::Boolean IsDisposed { System::Boolean get(); }

			private:
				System::Void Open(System::Boolean CreateIfNotExists, EArchiveFormat ArchiveFormat, System::UInt32 HashTableSize);
				System::Void Cleanup(System::Boolean CleanupManagedStuff);
				System::Void CheckBadState();

				System::UInt32 BuildFileFlags(ECompression Compression, EEncryption Encryption);
				System::UInt32 BuildWaveFlags(EQuality Quality);
				System::UInt32 BuildArchiveFlags(EArchiveFormat ArchiveFormat);

			private:
				HANDLE _Handle;
				System::String^ _FileName;

				System::Object^ _Tag;
				System::Boolean _Disposed;
		};
	}
}
