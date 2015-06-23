
// Product / Produit	:	KmsBase

/// \author	KMS -	Martin Dubois, ing.
/// \file	Includes/KmsLib/Windows/FileHandle.h

#pragma once

namespace KmsLib
{
	namespace Windows
	{

		/// \cond	en
		/// \brief	Wrap a file HANDLE
		/// \endcond
		/// \cond	fr
		/// \brief	Encapsule un HANDLE vers un fichier
		/// \endcond
		class FileHandle
		{

		public:

			/// \cond	en
			///	\brief	Constructor
			/// \endcond
			/// \cond	fr
			/// \brief	Constructeur
			/// \endcond
			FileHandle();

			/// \cond	en
			///	\brief	Destructor
			/// \endcond
			/// \cond	fr
			/// \brief	Destructeur
			/// \endcond
			/// \exception	Exception	CODE_IO_ERROR
			virtual ~FileHandle();

			/// \cond	en
			///	\brief	Cast operator
			/// \endcond
			/// \cond	fr
			/// \brief	Operateur de conversion
			/// \endcond
			operator HANDLE ();

			/// \cond	en
			///	\brief	Is the HANDLE open?
			/// \retval	false	The HANDLE is closed.
			/// \retval	true	The HANDLE is opened.
			/// \endcond
			/// \cond	fr
			/// \brief	Le HANDLE est-il ouver?
			/// \retval	false	Le HANDLE est Ferme.
			/// \retval	true	Le HANDLE est ouvert.
			/// \endcond
			bool	IsOpen() const;

			/// \cond	en
			///	\brief	See CloseHandle
			/// \endcond
			/// \cond	fr
			/// \brief	Voir CloseHandle
			/// \endcond
			/// \exception	Exception	CODE_IO_ERROR
			void Close();

			/// \cond	en
			///	\brief	See CreateFile
			/// \param	aFileName		[in]	Name of the file
			/// \param	aDesiredAccess			See GENERIC_...
			/// \param	aSharedMode				See ...
			/// \param	aCreationDisposition	See ...
			/// \param	aFlagsAndAttributes		See ...
			/// \endcond
			/// \cond	fr
			/// \brief	Voir CreateFileN		
			/// \param	aFileName		[in]	Nom du fichier
			/// \param	aDesiredAccess			Voir GENERIC_...
			/// \param	aSharedMode				Voir ...
			/// \param	aCreationDisposition	Voir ...
			/// \param	aFlagsAndAttributes		Voir ...
			/// \endcond
			/// \exception	Exception	CODE_IO_ERROR
			void Create(const char * aFileName, DWORD aDesiredAccess, DWORD aSharedMode, DWORD aCreationDisposition, DWORD aFlagsAndAttributes);

			/// \cond	en
			/// \brief	See ReadFile
			/// \param	aOut	[out]	Output buffer
			/// \param	aOutSize_byte	Size of the output buffer
			/// \return	This method returns the size of read data.
			/// \endcond
			/// \cond	fr
			/// \brief	Voir ReadFile
			/// \param	aOut	[out]	Espace memoire de sortie
			/// \param	aOutSize_byte	Taille de l'espace memoire de sortie
			/// \return	Cette method retourne la taille des donnees lu.
			/// \endcond
			/// \exception	Exception	CODE_IO_ERROR
			unsigned int	Read(void * aOut, unsigned int aOutSize_byte);

			/// \cond	en
			/// \brief	See WriteFile
			/// \param	aIn		[in]	Input buffer
			/// \param	aInSize_byte	Size of the input buffer
			/// \endcond
			/// \cond	fr
			/// \brief	Voir WriteFile
			/// \param	aIn		[in]	Espace memoire d'entree
			/// \param	aInSize_byte	Taille de l'espace memoire d'entree
			/// \endcond
			/// \exception	Exception	CODE_IO_ERROR
			void Write(const void * aIn, unsigned int aInSize_byte);

		protected:

			HANDLE mHandle;

		private:

			FileHandle(const FileHandle &);

			const FileHandle & operator = (const FileHandle &);

		};

		// Public
		/////////////////////////////////////////////////////////////////////

		// Return :
		//  false	= Le fichier est ouvert
		//  true	= Le fichier n'est pas ouvert
		inline bool FileHandle::IsOpen() const
		{
			return (INVALID_HANDLE_VALUE != mHandle);
		}

	}

}
