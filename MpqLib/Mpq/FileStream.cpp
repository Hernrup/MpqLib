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
#include "FileStream.h"

MpqLib::Mpq::CFileStream::CFileStream(CArchive^ Archive, System::String^ FileName)
{
	_Disposed = false;

	_Handle = INVALID_HANDLE_VALUE;
	_FileName = FileName;
	_Archive = Archive;
	
	_Length = 0;
	_Position = 0;
	_Cache = new std::vector<System::Byte>();

	Open();
}

MpqLib::Mpq::CFileStream::~CFileStream()
{
	Cleanup(true);
	_Disposed = true;
}

MpqLib::Mpq::CFileStream::!CFileStream()
{
	Cleanup(false);
	_Disposed = true;
}

System::Void MpqLib::Mpq::CFileStream::Close()
{
	if(_Disposed) throw gcnew System::ObjectDisposedException(nullptr, "The file stream has been disposed!");

	Cleanup(true);
}

array<System::Byte>^ MpqLib::Mpq::CFileStream::Read(System::Int32 Size)
{
	CheckBadState();

	System::Int32 BytesToRead = (_Position + Size > _Length) ? static_cast<System::Int32>(_Length - _Position) : Size;
	if(BytesToRead < 0) return nullptr;

	array<System::Byte>^ Buffer = gcnew array<System::Byte>(BytesToRead);
	if(BytesToRead == 0) return Buffer;

	Read(Buffer, 0, BytesToRead);

	return Buffer;
}

array<System::Byte>^ MpqLib::Mpq::CFileStream::Read(System::Int32 Position, System::Int32 Size)
{
	CheckBadState();

	Seek(Position, System::IO::SeekOrigin::Begin);

	return Read(Size);
}

System::Int32 MpqLib::Mpq::CFileStream::Read(array<System::Byte>^ Buffer, System::Int32 Index, System::Int32 Size)
{
	CheckBadState();

	if(Size <= 0) return 0;

	System::Int32 BytesToRead = (_Position + Size > _Length) ? static_cast<System::Int32>(_Length - _Position) : Size;
	System::Runtime::InteropServices::Marshal::Copy(static_cast<System::IntPtr>(&((*_Cache)[static_cast<System::Int32>(_Position)])), Buffer, Index, BytesToRead);
	_Position += BytesToRead;

	return BytesToRead;
}

System::Void MpqLib::Mpq::CFileStream::Write(array<System::Byte>^ Buffer, System::Int32 Index, System::Int32 Size)
{
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(Index);
	UNREFERENCED_PARAMETER(Size);

	CheckBadState();

	throw gcnew System::NotSupportedException("Writing is not supported!");
}

System::Int64 MpqLib::Mpq::CFileStream::Seek(System::Int64 Position, System::IO::SeekOrigin SeekOrigin)
{
	CheckBadState();

	switch(SeekOrigin)
	{
		case System::IO::SeekOrigin::Begin:
		{
			_Position = Position;
			break;
		}

		case System::IO::SeekOrigin::Current:
		{
			_Position += Position;
			break;
		}

		case System::IO::SeekOrigin::End:
		{
			_Position = Length + Position;
			break;
		}
	}

	if(_Position < 0) _Position = 0;
	if(_Position > _Length) _Position = _Length;

	return _Position;
}

System::Void MpqLib::Mpq::CFileStream::SetLength(System::Int64 Length)
{
	UNREFERENCED_PARAMETER(Length);

	CheckBadState();

	throw gcnew System::NotSupportedException("Writing is not supported!");
}

System::Void MpqLib::Mpq::CFileStream::Flush()
{
	CheckBadState();

	throw gcnew System::NotSupportedException("Writing is not supported!");
}

System::String^ MpqLib::Mpq::CFileStream::ToString()
{
	CheckBadState();

	return _FileName;
}

System::Boolean MpqLib::Mpq::CFileStream::CanSeek::get()
{
	CheckBadState();

	return true;
}

System::Boolean MpqLib::Mpq::CFileStream::CanRead::get()
{
	CheckBadState();

	return true;
}

System::Boolean MpqLib::Mpq::CFileStream::CanWrite::get()
{
	CheckBadState();

	return false;
}

System::Int64 MpqLib::Mpq::CFileStream::Length::get()
{
	CheckBadState();

	return _Length;
}

System::Int64 MpqLib::Mpq::CFileStream::Position::get()
{
	CheckBadState();

	return _Position;
}

System::Void MpqLib::Mpq::CFileStream::Position::set(System::Int64 Position)
{
	CheckBadState();

	Seek(Position, System::IO::SeekOrigin::Begin);
}

System::Int64 MpqLib::Mpq::CFileStream::CompressedLength::get()
{
	CheckBadState();

	//MHE
	System::Int64 val = 0;
	DWORD pcbLengthNeeded = 32;
	SFileGetFileInfo(_Handle, SFILE_INFO_COMPRESSED_SIZE,&val,32,&pcbLengthNeeded);
	return val;
}

LCID MpqLib::Mpq::CFileStream::Locale::get()
{
	CheckBadState();

	//MHE
	System::Int64 val = 0;
	DWORD pcbLengthNeeded = 32;
	SFileGetFileInfo(_Handle, SFILE_INFO_LOCALEID,&val,32,&pcbLengthNeeded);
	return val;
}

System::Void MpqLib::Mpq::CFileStream::Locale::set(LCID Locale)
{
	CheckBadState();

	if(!SFileSetFileLocale(_Handle, Locale)) throw gcnew System::ArgumentException("Unable to change the locale to " + Locale + "!", "Locale");
}

HANDLE MpqLib::Mpq::CFileStream::Handle::get()
{
	CheckBadState();

	return _Handle;
}

System::String^ MpqLib::Mpq::CFileStream::FileName::get()
{
	CheckBadState();

	return _FileName;
}

MpqLib::Mpq::CArchive^ MpqLib::Mpq::CFileStream::Archive::get()
{
	CheckBadState();

	return _Archive;
}

System::Object^ MpqLib::Mpq::CFileStream::Tag::get()
{
	return _Tag;
}

System::Void MpqLib::Mpq::CFileStream::Tag::set(System::Object^ Tag)
{
	_Tag = Tag;
}

System::Boolean MpqLib::Mpq::CFileStream::IsDisposed::get()
{
	return _Disposed;
}

System::Void MpqLib::Mpq::CFileStream::Open()
{
	System::Int32 BytesRead = 0;
	pin_ptr<HANDLE> HandlePointer = &_Handle;
	CStringHandle FileNameHandle(_FileName);

	if(_Archive == nullptr) throw gcnew System::InvalidOperationException("The file stream has no associated archive!");
	if(_Archive->IsDisposed) throw gcnew System::ObjectDisposedException(nullptr, "The archive of the file stream has been disposed!");
	if((_Archive->Handle == NULL) || (_Archive->Handle == INVALID_HANDLE_VALUE)) throw gcnew System::InvalidOperationException("The archive of the file stream has been closed!");

	if(!_Archive->FileExists(_FileName)) throw gcnew System::IO::FileNotFoundException("Could not find \"" + _FileName + "\"!", _FileName);
	if(!SFileOpenFileEx(_Archive->Handle, FileNameHandle.Value, SFILE_OPEN_FROM_MPQ, HandlePointer)) throw gcnew System::IO::IOException("Unable to open \"" + _FileName + "\"!");

	//MHE
	System::Int64 val = 0;
	DWORD pcbLengthNeeded = 32;
	SFileGetFileInfo(_Handle, SFILE_INFO_FILE_SIZE,&val,32,&pcbLengthNeeded);

	_Length = static_cast<int>(val);
	if(_Length < 0) _Length = 0;

	_Cache->resize(static_cast<System::UInt32>(_Length));

	if(!SFileReadFile(_Handle, &((*_Cache)[0]), static_cast<DWORD>(_Length), reinterpret_cast<LPDWORD>(&BytesRead), NULL)) throw gcnew System::IO::IOException("Read operation failed!");
	if(_Length != static_cast<System::Int64>(BytesRead)) throw gcnew System::IO::IOException("Read failed, expected " + _Length + " bytes, read " + BytesRead + " bytes!");

	_Position = 0;
}

System::Void MpqLib::Mpq::CFileStream::Cleanup(System::Boolean CleanupManagedStuff)
{
	UNREFERENCED_PARAMETER(CleanupManagedStuff);

	if(_Handle != NULL)
	{
		SFileCloseFile(_Handle);
		_Handle = NULL;
	}

	if(_Cache != NULL)
	{
		delete _Cache;
		_Cache = NULL;
	}
}

System::Void MpqLib::Mpq::CFileStream::CheckBadState()
{
	if(_Disposed) throw gcnew System::ObjectDisposedException(nullptr, "The file stream has been disposed!");
	if((_Handle == NULL) || (_Handle == INVALID_HANDLE_VALUE)) throw gcnew System::InvalidOperationException("The file stream has been closed!");
	if(_Archive->IsDisposed) throw gcnew System::ObjectDisposedException(nullptr, "The archive of the file stream has been disposed!");
	if((_Archive->Handle == NULL) || (_Archive->Handle == INVALID_HANDLE_VALUE)) throw gcnew System::InvalidOperationException("The archive of the file stream has been closed!");
}
