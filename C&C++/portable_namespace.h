#ifdef __cplusplus
namespace nm {
#else
# define fun NM_fun
#endif
	void fun() { int a = 12; }
#ifdef __cplusplus
}
#endif
