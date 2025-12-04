#include <curl/curl.h>

signed main(){
	CURL *curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, "http://fizika.pe.hu/Fizika/in/index.php");

	curl_easy_perform(curl);

	curl_easy_cleanup(curl);
	return 0;
}
