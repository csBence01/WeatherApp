#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>


using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;


int main() {
	// Create an HTTP client
	cout << "\t+-o-o-o-o-o-o-oo-" << endl;
	cout << "\t\tMy Weather App" << endl;
	cout << "\t+-o-o-o-o-o-o-oo-" << endl;
	cout << "\tEnter the city name: ";
	string city;
	getline(cin, city);

	http_client client(U("https://api.openweathermap.org/data/2.5"));
	uri_builder builder(U("/weather"));
	builder.append_query(U("q"), utility::conversions::to_string_t(city));
	builder.append_query(U("appid"), U("4a2a00643e34edfc7fac8a664c56050c"));
	http_request request(methods::GET);
	request.set_request_uri(builder.to_uri());

	client.request(request).then([](http_response response) {
		return response.extract_json();
	}
		).then([](web::json::value body) {
		cout << "\t Temperature:" << body[U("main")][U("temp")].as_double() << " K" << endl;
		cout << "\t Humidity:" << body[U("main")][U("humidity")].as_double() << " %" << endl;
		cout << "\t Weather:" << utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string());
	}
		).wait();
	return 0;
}



