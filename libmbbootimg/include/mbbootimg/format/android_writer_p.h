/*
 * Copyright (C) 2017-2018  Andrew Gunnerson <andrewgunnerson@gmail.com>
 *
 * This file is part of DualBootPatcher
 *
 * DualBootPatcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DualBootPatcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DualBootPatcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "mbbootimg/guard_p.h"

#include <optional>

#include "mbbootimg/format/android_p.h"
#include "mbbootimg/format/segment_writer_p.h"
#include "mbbootimg/sha1_p.h"
#include "mbbootimg/writer_p.h"


namespace mb::bootimg::android
{

class AndroidFormatWriter : public detail::FormatWriter
{
public:
    AndroidFormatWriter(bool is_bump) noexcept;
    virtual ~AndroidFormatWriter() noexcept;

    MB_DISABLE_COPY_CONSTRUCT_AND_ASSIGN(AndroidFormatWriter)
    MB_DEFAULT_MOVE_CONSTRUCT_AND_ASSIGN(AndroidFormatWriter)

    Format type() override;

    oc::result<void> open(File &file) override;
    oc::result<void> close(File &file) override;
    oc::result<Header> get_header(File &file) override;
    oc::result<void> write_header(File &file, const Header &header) override;
    oc::result<Entry> get_entry(File &file) override;
    oc::result<void> write_entry(File &file, const Entry &entry) override;
    oc::result<size_t> write_data(File &file, span<const unsigned char> buf) override;
    oc::result<void> finish_entry(File &file) override;

private:
    const bool m_is_bump;

    // Header values
    AndroidHeader m_hdr;

    detail::SHA1 m_sha1;

    std::optional<SegmentWriter> m_seg;
};

}
