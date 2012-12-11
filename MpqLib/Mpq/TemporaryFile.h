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

#include "Constants.h"

namespace MpqLib
{
	namespace Mpq
	{
		private ref class CTemporaryFile
		{
			public:
				CTemporaryFile();
				CTemporaryFile(array<System::Byte>^ FileData);
				~CTemporaryFile();
				!CTemporaryFile();

				System::Void CopyTo(array<System::Byte>^ FileData, System::Int32 Index);

				property System::String^ FileName { System::String^ get(); }

			private:
				void Cleanup(bool CleanupManagedStuff);

			private:
				bool Disposed;
				System::String^ _FileName;
		};
	}
}
