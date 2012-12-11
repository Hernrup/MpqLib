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
#include "Archive.h"

MpqLib::Mpq::CArchive::CArchive(System::String^ FileName)
{
	_Disposed = false;

	_Handle = NULL;
	_FileName = FileName;

	Open(false, EArchiveFormat::Version2, CConstants::DefaultHashTableSize);
}

MpqLib::Mpq::CArchive::CArchive(System::String^ FileName, System::Boolean CreateIfNotExists)
{
	_Disposed = false;

	_Handle = NULL;
	_FileName = FileName;

	Open(CreateIfNotExists, EArchiveFormat::Version2, CConstants::DefaultHashTableSize);
}

MpqLib::Mpq::CArchive::CArchive(System::String^ FileName, System::Boolean CreateIfNotExists, EArchiveFormat ArchiveFormat)
{
	_Disposed = false;

	_Handle = NULL;
	_FileName = FileName;

	Open(CreateIfNotExists, ArchiveFormat, CConstants::DefaultHashTableSize);
}

MpqLib::Mpq::CArchive::CArchive(System::String^ FileName, System::Boolean CreateIfNotExists, EArchiveFormat ArchiveFormat, System::UInt32 HashTableSize)
{
	_Disposed = false;

	_Handle = NULL;
	_FileName = FileName;

	Open(CreateIfNotExists, ArchiveFormat, HashTableSize);
}

MpqLib::Mpq::CArchive::~CArchive()
{
	Cleanup(true);
	_Disposed = true;
}

MpqLib::Mpq::CArchive::!CArchive()
{
	Cleanup(false);
	_Disposed = true;
}

System::Void MpqLib::Mpq::CArchive::Close()
{
	if(_Disposed) throw gcnew System::ObjectDisposedException(nullptr, "The archive has been disposed!");

	Cleanup(true);
}

System::Void MpqLib::Mpq::CArchive::Flush()
{
	CheckBadState();

	if(!SFileFlushArchive(_Handle)) throw gcnew System::IO::IOException("Flush operation failed!");
}

System::Void MpqLib::Mpq::CArchive::Compact()
{
	CheckBadState();

	if(!SFileCompactArchive(_Handle, NULL, FALSE)) throw gcnew System::IO::IOException("Compact operation failed!");
}

System::Boolean MpqLib::Mpq::CArchive::FileExists(System::String^ FileName)
{
	CheckBadState();

	CStringHandle FileNameHandle(FileName);

	return (SFileHasFile(_Handle, const_cast<LPSTR>(FileNameHandle.Value)) != 0);
}

System::Void MpqLib::Mpq::CArchive::ImportFile(System::String^ FileName, System::String^ RealFileName)
{
	CheckBadState();

	ImportFile(FileName, RealFileName, ECompression::None, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportFile(System::String^ FileName, System::String^ RealFileName, ECompression Compression)
{
	CheckBadState();

	ImportFile(FileName, RealFileName, Compression, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportFile(System::String^ FileName, System::String^ RealFileName, ECompression Compression, EEncryption Encryption)
{
	CheckBadState();

	CStringHandle FileNameHandle(FileName);
	CStringHandle RealFileNameHandle(RealFileName);

	throw gcnew System::IO::IOException("SFileAddFile obsolete");
	//MHE REMOVED
	//if(!SFileAddFile(_Handle, RealFileNameHandle.Value, FileNameHandle.Value, BuildFileFlags(Compression, Encryption))) throw gcnew System::IO::IOException("Unable to import \"" + RealFileName + "\" as \"" + FileName + "\"!");
}

System::Void MpqLib::Mpq::CArchive::ImportFile(System::String^ FileName, array<System::Byte>^ FileData)
{
	CheckBadState();

	ImportFile(FileName, FileData, ECompression::None, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportFile(System::String^ FileName, array<System::Byte>^ FileData, ECompression Compression)
{
	CheckBadState();

	ImportFile(FileName, FileData, Compression, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportFile(System::String^ FileName, array<System::Byte>^ FileData, ECompression Compression, EEncryption Encryption)
{
	CheckBadState();

	CTemporaryFile TemporaryFile(FileData);

	ImportFile(FileName, TemporaryFile.FileName, Compression, Encryption);
}

System::Void MpqLib::Mpq::CArchive::ImportWaveFile(System::String^ FileName, System::String^ RealFileName, EQuality Quality)
{
	CheckBadState();

	ImportWaveFile(FileName, RealFileName, Quality, ECompression::None, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportWaveFile(System::String^ FileName, System::String^ RealFileName, EQuality Quality, ECompression Compression)
{
	CheckBadState();

	ImportWaveFile(FileName, RealFileName, Quality, Compression, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportWaveFile(System::String^ FileName, System::String^ RealFileName, EQuality Quality, ECompression Compression, EEncryption Encryption)
{
	CheckBadState();

	CStringHandle FileNameHandle(FileName);
	CStringHandle RealFileNameHandle(RealFileName);

	throw gcnew System::IO::IOException("SFileAddWave obsolete");
	//MHE REMOVED
	//if(!SFileAddWave(_Handle, RealFileNameHandle.Value, FileNameHandle.Value, BuildFileFlags(Compression, Encryption), BuildWaveFlags(Quality))) throw gcnew System::IO::IOException("Unable to import \"" + RealFileName + "\" as \"" + FileName + "\"!");
}

System::Void MpqLib::Mpq::CArchive::ImportWaveFile(System::String^ FileName, array<System::Byte>^ FileData, EQuality Quality)
{
	CheckBadState();

	ImportWaveFile(FileName, FileData, Quality, ECompression::None, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportWaveFile(System::String^ FileName, array<System::Byte>^ FileData, EQuality Quality, ECompression Compression)
{
	CheckBadState();

	ImportWaveFile(FileName, FileData, Quality, Compression, EEncryption::None);
}

System::Void MpqLib::Mpq::CArchive::ImportWaveFile(System::String^ FileName, array<System::Byte>^ FileData, EQuality Quality, ECompression Compression, EEncryption Encryption)
{
	CheckBadState();

	CTemporaryFile TemporaryFile(FileData);

	ImportWaveFile(FileName, TemporaryFile.FileName, Quality, Compression, Encryption);
}

System::Void MpqLib::Mpq::CArchive::ImportListFile(System::String^ FileName)
{
	CheckBadState();

	CStringHandle FileNameHandle(FileName);

	if(SFileAddListFile(_Handle, FileNameHandle.Value) != ERROR_SUCCESS) throw gcnew System::IO::IOException("Unable to import the listfile \"" + FileName + "\"!");
}

System::Void MpqLib::Mpq::CArchive::ImportListFile(array<System::Byte>^ FileData)
{
	CheckBadState();

	CTemporaryFile TemporaryFile(FileData);

	ImportListFile(TemporaryFile.FileName);
}

System::Void MpqLib::Mpq::CArchive::ExportFile(System::String^ FileName, System::String^ RealFileName)
{
	CheckBadState();

	CStringHandle FileNameHandle(FileName);
	CStringHandle RealFileNameHandle(RealFileName);

	if(!SFileExtractFile(_Handle, FileNameHandle.Value, RealFileNameHandle.Value ,SFILE_OPEN_FROM_MPQ)) throw gcnew System::IO::IOException("Unable to export \"" + FileName + "\" as \"" + RealFileName + "\"!");
}

System::Void MpqLib::Mpq::CArchive::ExportFile(System::String^ FileName, array<System::Byte>^ FileData)
{
	CheckBadState();

	ExportFile(FileName, FileData, 0);
}

System::Void MpqLib::Mpq::CArchive::ExportFile(System::String^ FileName, array<System::Byte>^ FileData, System::Int32 Index)
{
	CheckBadState();

	CTemporaryFile TemporaryFile;

	ExportFile(FileName, TemporaryFile.FileName);
	TemporaryFile.CopyTo(FileData, Index);
}

System::Void MpqLib::Mpq::CArchive::RenameFile(System::String^ FileName, System::String^ NewFileName)
{
	CheckBadState();

	CStringHandle FileNameHandle(FileName);
	CStringHandle NewFileNameHandle(NewFileName);

	if(!SFileRenameFile(_Handle, FileNameHandle.Value, NewFileNameHandle.Value)) throw gcnew System::IO::IOException("Unable to rename \"" + FileName + "\" to \"" + NewFileName + "\"!");
}

System::Void MpqLib::Mpq::CArchive::RemoveFile(System::String^ FileName)
{
	CheckBadState();

	CStringHandle FileNameHandle(FileName);

	if(!SFileRemoveFile(_Handle, FileNameHandle.Value, SFILE_OPEN_FROM_MPQ)) throw gcnew System::IO::IOException("Unable to remove \"" + FileName + "\"!");
}

System::Collections::Generic::IEnumerable<MpqLib::Mpq::CFileInfo^>^ MpqLib::Mpq::CArchive::FindFiles(System::String^ Mask)
{
	CheckBadState();

	return FindFiles(Mask, nullptr, false);
}

System::Collections::Generic::IEnumerable<MpqLib::Mpq::CFileInfo^>^ MpqLib::Mpq::CArchive::FindFiles(System::String^ Mask, System::Boolean TraverseListFileOnly)
{
	CheckBadState();

	return FindFiles(Mask, nullptr, TraverseListFileOnly);
}

System::Collections::Generic::IEnumerable<MpqLib::Mpq::CFileInfo^>^ MpqLib::Mpq::CArchive::FindFiles(System::String^ Mask, System::String^ ExternalListFile)
{
	CheckBadState();

	return FindFiles(Mask, ExternalListFile, false);
}

System::Collections::Generic::IEnumerable<MpqLib::Mpq::CFileInfo^>^ MpqLib::Mpq::CArchive::FindFiles(System::String^ Mask, System::String^ ExternalListFile, System::Boolean TraverseListFileOnly)
{
	CheckBadState();

	CStringHandle MaskHandle(Mask);
	CStringHandle FileNameHandle((ExternalListFile != nullptr) ? ExternalListFile : "");
	System::Collections::Generic::List<MpqLib::Mpq::CFileInfo^>^ FileInfoList = gcnew System::Collections::Generic::List<MpqLib::Mpq::CFileInfo^>();

	if(TraverseListFileOnly)
	{
		SFILE_FIND_DATA SearchData;
		HANDLE SearchHandle = SListFileFindFirstFile(_Handle, ((ExternalListFile != nullptr) ? FileNameHandle.Value : NULL), MaskHandle.Value, &SearchData);
		if(SearchHandle == NULL) return FileInfoList;

		while(SearchHandle != NULL)
		{
			FileInfoList->Add(gcnew CFileInfo(gcnew System::String(SearchData.cFileName), SearchData.dwFileSize, SearchData.dwCompSize));
			if(!SListFileFindNextFile(SearchHandle, &SearchData)) break;
		}

		SListFileFindClose(SearchHandle);
	}
	else
	{
		SFILE_FIND_DATA SearchData;
		HANDLE SearchHandle = SFileFindFirstFile(_Handle, MaskHandle.Value, &SearchData, ((ExternalListFile != nullptr) ? FileNameHandle.Value : NULL));
		if(SearchHandle == NULL) return FileInfoList;

		while(SearchHandle != NULL)
		{
			FileInfoList->Add(gcnew CFileInfo(gcnew System::String(SearchData.cFileName), SearchData.dwFileSize, SearchData.dwCompSize));
			if(!SFileFindNextFile(SearchHandle, &SearchData)) break;
		}

		SFileFindClose(SearchHandle);
	}

	return FileInfoList;
}

System::String^ MpqLib::Mpq::CArchive::ToString()
{
	CheckBadState();

	return _FileName;
}

System::Int32 MpqLib::Mpq::CArchive::FileCount::get()
{
	CheckBadState();

	//MHE
	System::Int32 val = 0;
	DWORD pcbLengthNeeded = 32;
	SFileGetFileInfo(_Handle, SFILE_INFO_NUM_FILES,&val,32,&pcbLengthNeeded);
	return val;
}

LCID MpqLib::Mpq::CArchive::Locale::get()
{
	CheckBadState();

	return SFileGetLocale();
}

System::Void MpqLib::Mpq::CArchive::Locale::set(LCID Locale)
{
	CheckBadState();

	SFileSetLocale(Locale);
}

HANDLE MpqLib::Mpq::CArchive::Handle::get()
{
	CheckBadState();

	return _Handle;
}

System::String^ MpqLib::Mpq::CArchive::FileName::get()
{
	CheckBadState();

	return _FileName;
}

System::Object^ MpqLib::Mpq::CArchive::Tag::get()
{
	return _Tag;
}

System::Void MpqLib::Mpq::CArchive::Tag::set(System::Object^ Tag)
{
	_Tag = Tag;
}

System::Boolean MpqLib::Mpq::CArchive::IsDisposed::get()
{
	return _Disposed;
}

System::Void MpqLib::Mpq::CArchive::Open(System::Boolean CreateIfNotExists, EArchiveFormat ArchiveFormat, System::UInt32 HashTableSize)
{
	//MHE
	pin_ptr<HANDLE> HandlePointer = &_Handle;
	CStringHandle FileNameHandle(_FileName);

	if(System::IO::File::Exists(_FileName))
	{
		//if(!SFileCreateArchiveEx(FileNameHandle.Value, OPEN_EXISTING, 0, HandlePointer)) throw gcnew System::IO::IOException("Unable to open \"" + _FileName + "\"!");
		if(!SFileOpenArchive(FileNameHandle.Value, 0, BASE_PROVIDER_FILE, HandlePointer)) throw gcnew System::IO::IOException("Unable to open \"" + _FileName + "\"!");
	}
	else
	{
		throw gcnew System::IO::FileNotFoundException("Could not find \"" + _FileName + "\"!", _FileName);
		/*if(!CreateIfNotExists) throw gcnew System::IO::FileNotFoundException("Could not find \"" + _FileName + "\"!", _FileName);
		if(HashTableSize < HASH_TABLE_SIZE_MIN) throw gcnew System::ArgumentException("Hash table size must be at least " + HASH_TABLE_SIZE_MIN + "!");
		if(HashTableSize > HASH_TABLE_SIZE_MAX) throw gcnew System::ArgumentException("Hash table size can be at most " + HASH_TABLE_SIZE_MAX + "!");
		if(!SFileCreateArchiveEx(FileNameHandle.Value, BuildArchiveFlags(ArchiveFormat), HashTableSize, HandlePointer)) throw gcnew System::IO::IOException("Unable to open or create \"" + _FileName + "\"!");*/
	}
}

System::Void MpqLib::Mpq::CArchive::Cleanup(System::Boolean CleanupManagedStuff)
{
	UNREFERENCED_PARAMETER(CleanupManagedStuff);

	if(_Handle != NULL)
	{
		SFileCloseArchive(_Handle);
		_Handle = NULL;
	}
}

System::Void MpqLib::Mpq::CArchive::CheckBadState()
{
	if(_Disposed) throw gcnew System::ObjectDisposedException(nullptr, "The archive has been disposed!");
	if((_Handle == NULL) || (_Handle == INVALID_HANDLE_VALUE)) throw gcnew System::InvalidOperationException("The archive has been closed!");
}

System::UInt32 MpqLib::Mpq::CArchive::BuildFileFlags(ECompression Compression, EEncryption Encryption)
{
	System::UInt32 Flags = MPQ_FILE_REPLACEEXISTING;

	switch(Compression)
	{
	case ECompression::Implode:
		{
			Flags |= MPQ_FILE_IMPLODE;
			break;
		}

	case ECompression::Huffman:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_HUFFMANN;
			break;
		}

	case ECompression::ZLib:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_ZLIB;
			break;
		}

	case ECompression::PKWareDCL:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_PKWARE;
			break;
		}

	case ECompression::BZip2:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_BZIP2;
			break;
		}
	//MHE
	case ECompression::Sparse:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_SPARSE;
			break;
		}
	case ECompression::LZMA:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_LZMA;
			break;
		}
	case ECompression::ADPCM_MONO:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_ADPCM_MONO;
			break;
		}
	case ECompression::ADPCM_STEREO:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_ADPCM_STEREO;
			break;
		}
	/*case ECompression::WaveMono:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_WAVE_MONO;
			break;
		}

	case ECompression::WaveStereo:
		{
			Flags |= MPQ_FILE_COMPRESS | MPQ_COMPRESSION_WAVE_STEREO;
			break;
		}*/
	}

	switch(Encryption)
	{
	case EEncryption::Encrypted:
		{
			Flags |= MPQ_FILE_ENCRYPTED;
			break;
		}

	case EEncryption::EncryptedWithFixedSeed:
		{
			//MHE changed FIX_SEED to FiX_KEY
			Flags |= MPQ_FILE_ENCRYPTED | MPQ_FILE_FIX_KEY;
			break;
		}
	}

	return Flags;
}

System::UInt32 MpqLib::Mpq::CArchive::BuildWaveFlags(EQuality Quality)
{
	switch(Quality)
	{
	case EQuality::Low: return MPQ_WAVE_QUALITY_LOW;
	case EQuality::Medium: return MPQ_WAVE_QUALITY_MEDIUM;
	case EQuality::High: return MPQ_WAVE_QUALITY_HIGH;
	}

	return 0;
}

System::UInt32 MpqLib::Mpq::CArchive::BuildArchiveFlags(EArchiveFormat ArchiveFormat)
{
	System::UInt32 Flags = CREATE_ALWAYS;

	switch(ArchiveFormat)
	{
	case EArchiveFormat::Version1:
		{
			Flags |= MPQ_CREATE_ARCHIVE_V1;
			break;
		}

	case EArchiveFormat::Version2:
		{
			Flags |= MPQ_CREATE_ARCHIVE_V2;
			break;
		}
	}

	return Flags;
}
