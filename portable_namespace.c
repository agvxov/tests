#include "portable_namespace.h"

#ifdef __cplusplus
signed main() {
	nm::fun();
	return 0;
}
#else
signed main() {
	NM_fun();
	return 0;
}
#endif
