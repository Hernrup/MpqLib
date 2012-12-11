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
		/// <summary>
		/// Enumerates the available compression formats.
		/// </summary>
		public enum class ECompression
		{
			/// <summary>
			/// Represents no compression.
			/// </summary>
			None,

			/// <summary>
			/// Represents implode compression, PKWARE Data Compression Library.
			/// </summary>
			Implode,

			/// <summary>
			/// Represents extended huffman compression (used for wave files only).
			/// </summary>
			Huffman,

			/// <summary>
			/// Represents extended ZLIB compression.
			/// </summary>
			ZLib,

			/// <summary>
			/// Represents extended PKWare DCL compression.
			/// </summary>
			PKWareDCL,

			/// <summary>
			/// Represents extended BZip2 compression.
			/// </summary>
			BZip2,

			/// <summary>
			/// Represents extended wave (mono) compression.
			/// </summary>
			WaveMono,

			/// <summary>
			/// Represents extended wave (stereo) compression.
			/// </summary>
			WaveStereo,

			//MHE
			/// <summary>
			/// Represents Sparse compression.
			/// </summary>
			Sparse,

			/// <summary>
			/// Represents LZMA compression.
			/// </summary>
			LZMA,

			/// <summary>
			/// Represents ADPCM Mono compression.
			/// </summary>
			ADPCM_MONO,

			/// <summary>
			/// Represents ADPCM Stereo compression.
			/// </summary>
			ADPCM_STEREO,
		};
	}
}
