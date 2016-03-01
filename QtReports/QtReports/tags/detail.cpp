#include "detail.hpp"

namespace qtreports {
	namespace detail {

    Detail::Detail( ObjectPtr parent ) :
        Object( parent ) {}

    QString Detail::getClassName()
    {
        return QString("Detail");
    }

	}
}
