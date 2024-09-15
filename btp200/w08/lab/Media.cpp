#include "Media.h"

using namespace std;
namespace sdds {

	Media::~Media() {}

	std::ostream& operator<<(std::ostream& ostr, const Media& rhs)
	{
		rhs.play(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Media& rhs)
	{
		rhs.load(istr);
		return istr;
	}
}