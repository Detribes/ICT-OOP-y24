/*
  Zipios -- a small C++ library that provides easy access to .zip files.

  Copyright (C) 2000-2007  Thomas Sondergaard
  Copyright (c) 2015-2022  Made to Order Software Corp.  All Rights Reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/** \file
 * \brief Implementation of zipios::ZipInputStream.
 *
 * This file includes the implementation of the zipios::ZipInputStream
 * class which is a filter used to read files from Zip archives, files
 * that can be compressed using the zlib library.
 */

#include "zipinputstream.hpp"

#include <fstream>


namespace zipios
{


/** \class ZipInputStream
 * \brief The ZipInputStream to read data from a Zip archive.
 *
 * ZipInputStream is an istream that gets its input from a zip file. The
 * interface was redesigned in version 2.x to be more C++ like.
 *
 * \note
 * The getNextEntry() was removed because we cannot make it work here.
 * The old implementation would let someone read all the local directory
 * entries one after another. Only that is not correct and since this class
 * is not publicly exposed anymore, it wouldn't be available anyway.
 */


/** \brief Initialize a ZipInputStream from a filename and position.
 *
 * This constructor creates a ZIP file stream by attaching itself to
 * a file as defined by the specified filename and a position to the
 * header of the file being read.
 *
 * \param[in] filename  The name of a valid zip file.
 * \param[in] pos position to reposition the istream to before reading.
 */
ZipInputStream::ZipInputStream(std::string const& filename, std::streampos pos)
    : std::istream(nullptr)
    , m_ifs(new std::ifstream(filename, std::ios::in | std::ios::binary))
    , m_izf(new ZipInputStreambuf(m_ifs->rdbuf(), pos))
{
    // properly initialize the stream with the newly allocated buffer
    init(m_izf.get());
}



/** \brief Clean up the input stream.
 *
 * The destructor ensures that all resources used by the class get
 * released.
 */
ZipInputStream::~ZipInputStream()
{
}

/** \brief Close the current entry.
 *
 * This function closes the current entry, and positions the stream
 * read pointer at the beginning of the next entry (if there is one).
 */
    void ZipInputStream::closeEntry()
    {
        m_izf->closeEntry();
    }


/** \brief Close the input stream.
 *
 * This function closes the input stream. After that, the other functions
 * will most certainly not work anymore.
 */
    void ZipInputStream::close()
    {
        m_izf->close();
    }


/** \brief Get the next entry from the attached Zip archive.
 *
 * This function opens the next entry in the zip archive and returns
 * a pointer to a FileEntry object for the entry. For new instances
 * this method has to be called once before you can read from the
 * first entry.
 *
 * \return A list constant FileEntry pointers containing information
 *         about the (now) current entry.
 */
    FileEntry::pointer_t ZipInputStream::getNextEntry()
    {
        clear(); // clear eof and other flags.
        return m_izf->getNextEntry();
    }


} // zipios namespace

// Local Variables:
// mode: cpp
// indent-tabs-mode: nil
// c-basic-offset: 4
// tab-width: 4
// End:

// vim: ts=4 sw=4 et
