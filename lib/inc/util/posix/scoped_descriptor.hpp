#ifndef __POSIX_SCOPED_DESCRIPTOR_HPP__
#define __POSIX_SCOPED_DESCRIPTOR_HPP__

#include "../scoped_resource.hpp"
#include <unistd.h>

namespace cfacter { namespace util { namespace posix {
    /**
     * Represents a scoped file descriptor for POSIX systems.
     * Automatically closes the file descriptor when it goes out of scope.
    */
    struct scoped_descriptor : scoped_resource<int>
    {
        /**
         * Constructs a scoped_descriptor.
         * @param descriptor The file descriptor to close when destroyed.
         */
        scoped_descriptor(int descriptor) :
            scoped_resource(std::move(descriptor), close)
        {
        }

    private:
        static void close(int descriptor)
        {
            if (descriptor >= 0) {
                ::close(descriptor);
            }
        }
    };

} } } // namespace cfacter::util::posix

#endif
