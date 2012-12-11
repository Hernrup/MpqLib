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

#include "Archive.h"

namespace MpqLib
{
	namespace Mpq
	{
		/// <summary>
		/// Represents a file inside an MPQ archive. The stream is readonly.
		/// Use the archive Import-methods to update files in the archive.
		/// </summary>
		public ref class CFileStream sealed : System::IO::Stream
		{
			public:
				/// <summary>
				/// Parameterized constructor.
				/// </summary>
				/// <param name="Archive">The archive to stream a file from</param>
				/// <param name="FileName">The file to stream</param>
				CFileStream(CArchive^ Archive, System::String^ FileName);

				/// <summary>
				/// Releases all resources used by the MpqLib.Mpq.CFileStream.
				/// </summary>
				~CFileStream();

				/// <summary>
				/// Releases all resources used by the MpqLib.Mpq.CFileStream.
				/// </summary>
				!CFileStream();

				/// <summary>
				/// Closes the file.
				/// </summary>
				virtual System::Void Close() override;

				/// <summary>
				/// Reads a number of bytes from the file, starting at the current position.
				/// </summary>
				/// <param name="Size">The (maximum) number of bytes to read</param>
				/// <returns>An array containing the bytes read</returns>
				array<System::Byte>^ Read(System::Int32 Size);

				/// <summary>
				/// Reads a number of bytes from the file, starting at the specified position.
				/// </summary>
				/// <param name="Position">The position to start reading at</param>
				/// <param name="Size">The (maximum) number of bytes to read</param>
				/// <returns>An array containing the bytes read</returns>
				array<System::Byte>^ Read(System::Int32 Position, System::Int32 Size);

				/// <summary>
				/// Reads a number of bytes from the file to a buffer, starting at the current position.
				/// </summary>
				/// <param name="Buffer">The buffer to read into</param>
				/// <param name="Index">The index in the buffer to start writing at</param>
				/// <param name="Size">The (maximum) number of bytes to read</param>
				/// <returns>The number of bytes read</returns>
				virtual System::Int32 Read(array<System::Byte>^ Buffer, System::Int32 Index, System::Int32 Size) override;

				/// <summary>
				/// Writes a number of bytes to the file from a buffer, starting at the current position.
				/// </summary>
				/// <param name="Buffer">The buffer to write from</param>
				/// <param name="Index">The index in the buffer to start reading from</param>
				/// <param name="Size">The number of bytes to write</param>
				virtual System::Void Write(array<System::Byte>^ Buffer, System::Int32 Index, System::Int32 Size) override;

				/// <summary>
				/// Updates the current position (no reading or writing performed).
				/// </summary>
				/// <param name="Position">The new position to set, an offset relative to SeekOrigin</param>
				/// <param name="SeekOrigin">Where the new position should be relative from</param>
				/// <returns>The new position</returns>
				virtual System::Int64 Seek(System::Int64 Position, System::IO::SeekOrigin SeekOrigin) override;

				/// <summary>
				/// Changes the length (size) of the file, either extending or cutting off from the end.
				/// </summary>
				/// <param name="Length">The new length of the file</param>
				virtual System::Void SetLength(System::Int64 Length) override;

				/// <summary>
				/// Flushes the file, committing unsaved changes.
				/// </summary>
				virtual System::Void Flush() override;

				/// <summary>
				/// Generates a string version of the file.
				/// </summary>
				/// <returns>The generated string</returns>
				virtual System::String^ ToString() override;

				/// <summary>
				/// Checks if seeking can be performed on the stream.
				/// </summary>
				virtual property System::Boolean CanSeek { System::Boolean get() override; }

				/// <summary>
				/// Checks if the stream can be read from.
				/// </summary>
				virtual property System::Boolean CanRead { System::Boolean get() override; }

				/// <summary>
				/// Checks if the stream can be written to.
				/// </summary>
				virtual property System::Boolean CanWrite { System::Boolean get() override; }

				/// <summary>
				/// Retrieves the length (size) of the file.
				/// </summary>
				virtual property System::Int64 Length { System::Int64 get() override; }

				/// <summary>
				/// Gets or sets the current position in the file.
				/// </summary>
				virtual property System::Int64 Position { System::Int64 get() override; System::Void set(System::Int64 Position) override; }

				/// <summary>
				/// Retrieves the length (size) of the file when stored in the archive.
				/// </summary>
				property System::Int64 CompressedLength { System::Int64 get(); }

				/// <summary>
				/// Gets or sets the file locale (for language specific files).
				/// </summary>
				property LCID Locale { LCID get(); System::Void set(LCID Locale); }

				/// <summary>
				/// Retrieves the file handle.
				/// </summary>
				property HANDLE Handle { HANDLE get(); }

				/// <summary>
				/// Retrieves the file filename.
				/// </summary>
				property System::String^ FileName { System::String^ get(); }

				/// <summary>
				/// Retrieves the archive the file is located in.
				/// </summary>
				property CArchive^ Archive { CArchive^ get(); }

				/// <summary>
				/// Gets or sets the tag data of the file.
				/// </summary>
				property System::Object^ Tag { System::Object^ get(); System::Void set(System::Object^ Tag); }

				/// <summary>
				/// Checks if the file has been disposed.
				/// </summary>
				property System::Boolean IsDisposed { System::Boolean get(); }

			private:
				System::Void Open();
				System::Void Cleanup(System::Boolean CleanupManagedStuff);
				System::Void CheckBadState();

			private:
				HANDLE _Handle;
				System::String^ _FileName;
				CArchive^ _Archive;

				System::Int64 _Length;
				System::Int64 _Position;
				std::vector<System::Byte>* _Cache;

				System::Object^ _Tag;
				System::Boolean _Disposed;
		};
	}
}
