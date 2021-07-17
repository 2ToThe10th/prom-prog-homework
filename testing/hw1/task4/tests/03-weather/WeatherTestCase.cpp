//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::_;
using ::testing::Return;

const std::string kExampleDataBaseOdessa =
    R"({"coord":{"lon":30.7326,"lat":46.4775},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01n"}],"base":"stations","main":{"temp":11.84,"feels_like":10.8,"temp_min":11.67,"temp_max":12,"pressure":1014,"humidity":66},"visibility":10000,"wind":{"speed":5,"deg":340},"clouds":{"all":0},"dt":1620071762,"sys":{"type":1,"id":8915,"country":"UA","sunrise":1620009582,"sunset":1620061683},"timezone":10800,"id":698740,"name":"Odesa","cod":200})";

const std::string kExampleJSONNoWeather =
    R"({"list":{"lon":30.7326,"lat":46.4775}})";

const std::string kExampleJSONNoMain1 =
    R"({"list":[1, 2, 3, 4, 5, 6, 7, 8]})";

const std::string kExampleJSONNoMain2 =
    R"({"list":[1, 2, 3, 4, 5, 6, 7, {"x": "y"}]})";

const std::string kExampleJSONNoTemp1 =
    R"({"list":[1, 2, 3, 4, 5, 6, 7, {"main": "xxxx"}]})";

const std::string kExampleJSONNoTemp2 =
    R"({"list":[1, 2, 3, 4, 5, 6, 7, {"main": {"x": "y"}}}]})";

const std::string kExampleJSONIncorrectTemp =
    R"({"list":[1, 2, 3, 4, 5, 6, 7, {"main": {"temp": "y"}}}]})";

const std::string kNoJSON =
    R"({"coord{"lon:30.7326,"lat":46.4775}})";

const std::string kNoMain =
    R"({"coord": {"lon":30.7326,"lat":46.4775}})";

const std::string kNoTemp =
    R"({"main": {"lon":30.7326,"lat":46.4775}})";

const std::string kIncorrectTemp =
    R"({"main": {"temp":"y","lat":46.4775}})";

const std::string kExampleDataBaseMoscow =
    R"({"coord":{"lon":37.6156,"lat":55.7522},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01n"}],"base":"stations","main":{"temp":9.21,"feels_like":5.92,"temp_min":8.89,"temp_max":10,"pressure":998,"humidity":62},"visibility":10000,"wind":{"speed":7,"deg":260},"clouds":{"all":0},"dt":1620071732,"sys":{"type":1,"id":9027,"country":"RU","sunrise":1620006120,"sunset":1620061842},"timezone":10800,"id":524901,"name":"Moscow","cod":200})";

const std::string kExampleDataForecast =
    R"({"cod":"200","message":0,"cnt":40,"list":[{"dt":1620075600,"main":{"temp":11.84,"feels_like":10.8,"temp_min":11.62,"temp_max":11.84,"pressure":1014,"sea_level":1014,"grnd_level":1010,"humidity":66,"temp_kf":0.22},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01n"}],"clouds":{"all":0},"wind":{"speed":5.98,"deg":336,"gust":11.63},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-03 21:00:00"},{"dt":1620086400,"main":{"temp":11.15,"feels_like":10.02,"temp_min":9.78,"temp_max":11.15,"pressure":1015,"sea_level":1015,"grnd_level":1011,"humidity":65,"temp_kf":1.37},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03n"}],"clouds":{"all":25},"wind":{"speed":5.51,"deg":338,"gust":9.58},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-04 00:00:00"},{"dt":1620097200,"main":{"temp":9.53,"feels_like":7.33,"temp_min":8.38,"temp_max":9.53,"pressure":1017,"sea_level":1017,"grnd_level":1012,"humidity":69,"temp_kf":1.15},"weather":[{"id":801,"main":"Clouds","description":"few clouds","icon":"02d"}],"clouds":{"all":18},"wind":{"speed":4.2,"deg":329,"gust":7.83},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-04 03:00:00"},{"dt":1620108000,"main":{"temp":11.19,"feels_like":9.85,"temp_min":11.19,"temp_max":11.19,"pressure":1020,"sea_level":1020,"grnd_level":1013,"humidity":57,"temp_kf":0},"weather":[{"id":801,"main":"Clouds","description":"few clouds","icon":"02d"}],"clouds":{"all":17},"wind":{"speed":4.5,"deg":321,"gust":5.93},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-04 06:00:00"},{"dt":1620118800,"main":{"temp":14.03,"feels_like":12.69,"temp_min":14.03,"temp_max":14.03,"pressure":1019,"sea_level":1019,"grnd_level":1013,"humidity":46,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":8},"wind":{"speed":4.04,"deg":297,"gust":5.34},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-04 09:00:00"},{"dt":1620129600,"main":{"temp":15.78,"feels_like":14.48,"temp_min":15.78,"temp_max":15.78,"pressure":1018,"sea_level":1018,"grnd_level":1012,"humidity":41,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03d"}],"clouds":{"all":34},"wind":{"speed":4.39,"deg":300,"gust":5.91},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-04 12:00:00"},{"dt":1620140400,"main":{"temp":15.46,"feels_like":14.18,"temp_min":15.46,"temp_max":15.46,"pressure":1018,"sea_level":1018,"grnd_level":1012,"humidity":43,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"clouds":{"all":90},"wind":{"speed":2.57,"deg":325,"gust":4.55},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-04 15:00:00"},{"dt":1620151200,"main":{"temp":12.13,"feels_like":11.07,"temp_min":12.13,"temp_max":12.13,"pressure":1019,"sea_level":1019,"grnd_level":1012,"humidity":64,"temp_kf":0},"weather":[{"id":803,"main":"Clouds","description":"broken clouds","icon":"04n"}],"clouds":{"all":59},"wind":{"speed":3.59,"deg":197,"gust":4.46},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-04 18:00:00"},{"dt":1620162000,"main":{"temp":10.92,"feels_like":10.05,"temp_min":10.92,"temp_max":10.92,"pressure":1019,"sea_level":1019,"grnd_level":1013,"humidity":76,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01n"}],"clouds":{"all":8},"wind":{"speed":4.01,"deg":207,"gust":6.49},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-04 21:00:00"},{"dt":1620172800,"main":{"temp":10.49,"feels_like":9.68,"temp_min":10.49,"temp_max":10.49,"pressure":1018,"sea_level":1018,"grnd_level":1012,"humidity":80,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01n"}],"clouds":{"all":6},"wind":{"speed":3.9,"deg":207,"gust":7.13},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-05 00:00:00"},{"dt":1620183600,"main":{"temp":10.43,"feels_like":9.62,"temp_min":10.43,"temp_max":10.43,"pressure":1018,"sea_level":1018,"grnd_level":1011,"humidity":80,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":0},"wind":{"speed":3.89,"deg":197,"gust":7.21},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-05 03:00:00"},{"dt":1620194400,"main":{"temp":13.06,"feels_like":12.01,"temp_min":13.06,"temp_max":13.06,"pressure":1018,"sea_level":1018,"grnd_level":1012,"humidity":61,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":0},"wind":{"speed":5.53,"deg":173,"gust":7.41},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-05 06:00:00"},{"dt":1620205200,"main":{"temp":13.84,"feels_like":12.69,"temp_min":13.84,"temp_max":13.84,"pressure":1018,"sea_level":1018,"grnd_level":1012,"humidity":54,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":0},"wind":{"speed":6.37,"deg":161,"gust":7.32},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-05 09:00:00"},{"dt":1620216000,"main":{"temp":13.88,"feels_like":12.79,"temp_min":13.88,"temp_max":13.88,"pressure":1017,"sea_level":1017,"grnd_level":1011,"humidity":56,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":0},"wind":{"speed":6.3,"deg":160,"gust":7.83},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-05 12:00:00"},{"dt":1620226800,"main":{"temp":13.06,"feels_like":11.99,"temp_min":13.06,"temp_max":13.06,"pressure":1016,"sea_level":1016,"grnd_level":1009,"humidity":60,"temp_kf":0},"weather":[{"id":800,"main":"Clear","description":"clear sky","icon":"01d"}],"clouds":{"all":2},"wind":{"speed":5.79,"deg":154,"gust":7.89},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-05 15:00:00"},{"dt":1620237600,"main":{"temp":11.59,"feels_like":10.84,"temp_min":11.59,"temp_max":11.59,"pressure":1016,"sea_level":1016,"grnd_level":1009,"humidity":78,"temp_kf":0},"weather":[{"id":801,"main":"Clouds","description":"few clouds","icon":"02n"}],"clouds":{"all":23},"wind":{"speed":5.67,"deg":170,"gust":9.65},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-05 18:00:00"},{"dt":1620248400,"main":{"temp":11.07,"feels_like":10.32,"temp_min":11.07,"temp_max":11.07,"pressure":1015,"sea_level":1015,"grnd_level":1009,"humidity":80,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03n"}],"clouds":{"all":32},"wind":{"speed":5.19,"deg":181,"gust":9.98},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-05 21:00:00"},{"dt":1620259200,"main":{"temp":10.98,"feels_like":10.2,"temp_min":10.98,"temp_max":10.98,"pressure":1014,"sea_level":1014,"grnd_level":1007,"humidity":79,"temp_kf":0},"weather":[{"id":803,"main":"Clouds","description":"broken clouds","icon":"04n"}],"clouds":{"all":51},"wind":{"speed":4.87,"deg":175,"gust":8.87},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-06 00:00:00"},{"dt":1620270000,"main":{"temp":11.05,"feels_like":10.25,"temp_min":11.05,"temp_max":11.05,"pressure":1014,"sea_level":1014,"grnd_level":1008,"humidity":78,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"clouds":{"all":100},"wind":{"speed":4.91,"deg":181,"gust":9.31},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-06 03:00:00"},{"dt":1620280800,"main":{"temp":13.29,"feels_like":12.27,"temp_min":13.29,"temp_max":13.29,"pressure":1015,"sea_level":1015,"grnd_level":1008,"humidity":61,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"clouds":{"all":99},"wind":{"speed":6.13,"deg":183,"gust":8.77},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-06 06:00:00"},{"dt":1620291600,"main":{"temp":14.65,"feels_like":13.66,"temp_min":14.65,"temp_max":14.65,"pressure":1015,"sea_level":1015,"grnd_level":1009,"humidity":57,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"clouds":{"all":100},"wind":{"speed":6.52,"deg":184,"gust":7.92},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-06 09:00:00"},{"dt":1620302400,"main":{"temp":15.41,"feels_like":14.44,"temp_min":15.41,"temp_max":15.41,"pressure":1015,"sea_level":1015,"grnd_level":1009,"humidity":55,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"clouds":{"all":90},"wind":{"speed":5.63,"deg":184,"gust":5.99},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-06 12:00:00"},{"dt":1620313200,"main":{"temp":14.71,"feels_like":13.78,"temp_min":14.71,"temp_max":14.71,"pressure":1015,"sea_level":1015,"grnd_level":1008,"humidity":59,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03d"}],"clouds":{"all":35},"wind":{"speed":4.92,"deg":174,"gust":4.76},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-06 15:00:00"},{"dt":1620324000,"main":{"temp":12.83,"feels_like":11.89,"temp_min":12.83,"temp_max":12.83,"pressure":1016,"sea_level":1016,"grnd_level":1009,"humidity":66,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03n"}],"clouds":{"all":37},"wind":{"speed":4.15,"deg":183,"gust":5.88},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-06 18:00:00"},{"dt":1620334800,"main":{"temp":12.51,"feels_like":11.62,"temp_min":12.51,"temp_max":12.51,"pressure":1016,"sea_level":1016,"grnd_level":1010,"humidity":69,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04n"}],"clouds":{"all":99},"wind":{"speed":4.14,"deg":203,"gust":6.91},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-06 21:00:00"},{"dt":1620345600,"main":{"temp":12.14,"feels_like":11.32,"temp_min":12.14,"temp_max":12.14,"pressure":1016,"sea_level":1016,"grnd_level":1009,"humidity":73,"temp_kf":0},"weather":[{"id":803,"main":"Clouds","description":"broken clouds","icon":"04n"}],"clouds":{"all":84},"wind":{"speed":3.72,"deg":219,"gust":6.84},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-07 00:00:00"},{"dt":1620356400,"main":{"temp":12.27,"feels_like":11.51,"temp_min":12.27,"temp_max":12.27,"pressure":1015,"sea_level":1015,"grnd_level":1008,"humidity":75,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04d"}],"clouds":{"all":91},"wind":{"speed":3.57,"deg":203,"gust":7.12},"visibility":10000,"pop":0.04,"sys":{"pod":"d"},"dt_txt":"2021-05-07 03:00:00"},{"dt":1620367200,"main":{"temp":14.58,"feels_like":13.82,"temp_min":14.58,"temp_max":14.58,"pressure":1016,"sea_level":1016,"grnd_level":1009,"humidity":66,"temp_kf":0},"weather":[{"id":803,"main":"Clouds","description":"broken clouds","icon":"04d"}],"clouds":{"all":81},"wind":{"speed":4.5,"deg":188,"gust":6.23},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-07 06:00:00"},{"dt":1620378000,"main":{"temp":15.86,"feels_like":15.3,"temp_min":15.86,"temp_max":15.86,"pressure":1016,"sea_level":1016,"grnd_level":1009,"humidity":69,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03d"}],"clouds":{"all":49},"wind":{"speed":6.01,"deg":171,"gust":6.73},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-07 09:00:00"},{"dt":1620388800,"main":{"temp":15.91,"feels_like":15.44,"temp_min":15.91,"temp_max":15.91,"pressure":1014,"sea_level":1014,"grnd_level":1008,"humidity":72,"temp_kf":0},"weather":[{"id":803,"main":"Clouds","description":"broken clouds","icon":"04d"}],"clouds":{"all":59},"wind":{"speed":7,"deg":170,"gust":7.79},"visibility":10000,"pop":0.12,"sys":{"pod":"d"},"dt_txt":"2021-05-07 12:00:00"},{"dt":1620399600,"main":{"temp":14.69,"feels_like":14.28,"temp_min":14.69,"temp_max":14.69,"pressure":1013,"sea_level":1013,"grnd_level":1007,"humidity":79,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03d"}],"clouds":{"all":49},"wind":{"speed":6.65,"deg":178,"gust":9.67},"visibility":10000,"pop":0.12,"sys":{"pod":"d"},"dt_txt":"2021-05-07 15:00:00"},{"dt":1620410400,"main":{"temp":14.01,"feels_like":13.61,"temp_min":14.01,"temp_max":14.01,"pressure":1013,"sea_level":1013,"grnd_level":1007,"humidity":82,"temp_kf":0},"weather":[{"id":803,"main":"Clouds","description":"broken clouds","icon":"04n"}],"clouds":{"all":71},"wind":{"speed":6.43,"deg":181,"gust":12.33},"visibility":10000,"pop":0.08,"sys":{"pod":"n"},"dt_txt":"2021-05-07 18:00:00"},{"dt":1620421200,"main":{"temp":14.36,"feels_like":13.91,"temp_min":14.36,"temp_max":14.36,"pressure":1012,"sea_level":1012,"grnd_level":1006,"humidity":79,"temp_kf":0},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04n"}],"clouds":{"all":100},"wind":{"speed":7.84,"deg":193,"gust":14.89},"visibility":10000,"pop":0.2,"sys":{"pod":"n"},"dt_txt":"2021-05-07 21:00:00"},{"dt":1620432000,"main":{"temp":13.15,"feels_like":12.71,"temp_min":13.15,"temp_max":13.15,"pressure":1011,"sea_level":1011,"grnd_level":1005,"humidity":84,"temp_kf":0},"weather":[{"id":500,"main":"Rain","description":"light rain","icon":"10n"}],"clouds":{"all":100},"wind":{"speed":7.58,"deg":188,"gust":14.56},"visibility":10000,"pop":0.39,"rain":{"3h":0.5},"sys":{"pod":"n"},"dt_txt":"2021-05-08 00:00:00"},{"dt":1620442800,"main":{"temp":12.96,"feels_like":12.53,"temp_min":12.96,"temp_max":12.96,"pressure":1010,"sea_level":1010,"grnd_level":1004,"humidity":85,"temp_kf":0},"weather":[{"id":500,"main":"Rain","description":"light rain","icon":"10d"}],"clouds":{"all":98},"wind":{"speed":6.75,"deg":196,"gust":13.83},"visibility":10000,"pop":0.24,"rain":{"3h":0.17},"sys":{"pod":"d"},"dt_txt":"2021-05-08 03:00:00"},{"dt":1620453600,"main":{"temp":15,"feels_like":14.46,"temp_min":15,"temp_max":15,"pressure":1010,"sea_level":1010,"grnd_level":1003,"humidity":73,"temp_kf":0},"weather":[{"id":500,"main":"Rain","description":"light rain","icon":"10d"}],"clouds":{"all":99},"wind":{"speed":8.32,"deg":200,"gust":15.11},"visibility":10000,"pop":0.31,"rain":{"3h":0.29},"sys":{"pod":"d"},"dt_txt":"2021-05-08 06:00:00"},{"dt":1620464400,"main":{"temp":18.3,"feels_like":17.99,"temp_min":18.3,"temp_max":18.3,"pressure":1010,"sea_level":1010,"grnd_level":1003,"humidity":69,"temp_kf":0},"weather":[{"id":500,"main":"Rain","description":"light rain","icon":"10d"}],"clouds":{"all":100},"wind":{"speed":7.35,"deg":240,"gust":11.32},"visibility":10000,"pop":0.42,"rain":{"3h":0.3},"sys":{"pod":"d"},"dt_txt":"2021-05-08 09:00:00"},{"dt":1620475200,"main":{"temp":15.1,"feels_like":14.31,"temp_min":15.1,"temp_max":15.1,"pressure":1013,"sea_level":1013,"grnd_level":1006,"humidity":63,"temp_kf":0},"weather":[{"id":500,"main":"Rain","description":"light rain","icon":"10d"}],"clouds":{"all":100},"wind":{"speed":10.73,"deg":329,"gust":12.91},"visibility":10000,"pop":0.37,"rain":{"3h":0.26},"sys":{"pod":"d"},"dt_txt":"2021-05-08 12:00:00"},{"dt":1620486000,"main":{"temp":13.61,"feels_like":12.62,"temp_min":13.61,"temp_max":13.61,"pressure":1015,"sea_level":1015,"grnd_level":1009,"humidity":61,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03d"}],"clouds":{"all":43},"wind":{"speed":9.66,"deg":334,"gust":12.16},"visibility":10000,"pop":0,"sys":{"pod":"d"},"dt_txt":"2021-05-08 15:00:00"},{"dt":1620496800,"main":{"temp":10.91,"feels_like":9.62,"temp_min":10.91,"temp_max":10.91,"pressure":1019,"sea_level":1019,"grnd_level":1012,"humidity":60,"temp_kf":0},"weather":[{"id":802,"main":"Clouds","description":"scattered clouds","icon":"03n"}],"clouds":{"all":47},"wind":{"speed":7.09,"deg":348,"gust":11.22},"visibility":10000,"pop":0,"sys":{"pod":"n"},"dt_txt":"2021-05-08 18:00:00"}],"city":{"id":698740,"name":"Odesa","coord":{"lat":46.4775,"lon":30.7326},"country":"UA","population":1001558,"timezone":10800,"sunrise":1620009582,"sunset":1620061683}})";

const int kStatusCode = 200;
const double kElapsed = 0.1;

auto GetResponseWithData(const std::string &data) {
  return cpr::Response(kStatusCode,
                       data,
                       cpr::Header{},
                       "",
                       kElapsed,
                       cpr::Cookies{},
                       cpr::Error{});
}

TEST_F(WeatherTestCase, BadResponceTemperature) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).WillOnce(Return(cpr::Response()));
  EXPECT_THROW(weather.GetTemperature("Odessa"), std::invalid_argument);
}

TEST_F(WeatherTestCase, BadResponceTomorrowTemperature) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).WillOnce(Return(cpr::Response()));
  EXPECT_THROW(weather.GetTomorrowTemperature("Odessa"), std::invalid_argument);
}

TEST_F(WeatherTestCase, BadJSONTomorrowTemperature) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).Times(7).WillOnce(Return(GetResponseWithData(kNoJSON)))
      .WillOnce(Return(GetResponseWithData(kExampleJSONNoWeather)))
      .WillOnce(Return(GetResponseWithData(kExampleJSONNoMain1)))
      .WillOnce(Return(GetResponseWithData(kExampleJSONNoMain2)))
      .WillOnce(Return(GetResponseWithData(kExampleJSONNoTemp1)))
      .WillOnce(Return(GetResponseWithData(kExampleJSONNoTemp2)))
      .WillOnce(Return(GetResponseWithData(kExampleJSONIncorrectTemp)));
  EXPECT_ANY_THROW(weather.GetTomorrowTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTomorrowTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTomorrowTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTomorrowTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTomorrowTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTomorrowTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTomorrowTemperature("Odessa"));
}

TEST_F(WeatherTestCase, BadResponceDifferenceString) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).WillOnce(Return(cpr::Response()));
  EXPECT_THROW(weather.GetDifferenceString("Odessa", "Moscow"), std::invalid_argument);
}

TEST_F(WeatherTestCase, BadResponceTomorrowDiff) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _))
      .WillOnce(Return(cpr::Response()))
      .WillOnce(Return(GetResponseWithData(kExampleDataForecast)))
      .WillOnce(Return(cpr::Response()));
  EXPECT_THROW(weather.GetTomorrowDiff("Odessa"), std::invalid_argument);
  EXPECT_THROW(weather.GetTomorrowDiff("Odessa"), std::invalid_argument);
}

TEST_F(WeatherTestCase, Temperature) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).WillOnce(Return(GetResponseWithData(kExampleDataBaseOdessa)));
  EXPECT_NEAR(weather.GetTemperature("Odessa"), 11.84, 0.01);
}

TEST_F(WeatherTestCase, JSONParse) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).Times(4)
  .WillOnce(Return(GetResponseWithData(kNoJSON)))
  .WillOnce(Return(GetResponseWithData(kNoMain)))
  .WillOnce(Return(GetResponseWithData(kNoTemp)))
  .WillOnce(Return(GetResponseWithData(kIncorrectTemp)));
  EXPECT_ANY_THROW(weather.GetTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTemperature("Odessa"));
  EXPECT_ANY_THROW(weather.GetTemperature("Odessa"));
}

TEST_F(WeatherTestCase, TemperatureBadJSON) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).WillOnce(Return(GetResponseWithData(kExampleJSONNoWeather)));
  EXPECT_ANY_THROW(weather.GetTemperature("Odessa"));
}

TEST_F(WeatherTestCase, DifferenceString) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).Times(2).WillRepeatedly(Return(GetResponseWithData(kExampleDataBaseOdessa)));
  EXPECT_CALL(weather, Get("Moscow", _)).Times(2).WillRepeatedly(Return(GetResponseWithData(kExampleDataBaseMoscow)));
  EXPECT_EQ(weather.GetDifferenceString("Odessa", "Moscow"), "Weather in Odessa is warmer than in Moscow by 2 degrees");
  EXPECT_EQ(weather.GetDifferenceString("Moscow", "Odessa"), "Weather in Moscow is colder than in Odessa by 2 degrees");
}

TEST_F(WeatherTestCase, CheckGet) {
  NiceMock<WeatherMock> weather;

  weather.SetApiKey("xyzzyx");

  EXPECT_EQ(weather.JustGet("X", cpr::Url{"https://notexistsite.com"}).status_code, 0);
}

TEST_F(WeatherTestCase, TomorrowDiff) {
  StrictMock<WeatherMock> weather;
  EXPECT_CALL(weather, Get("Odessa", _)).Times(2)
      .WillOnce(Return(GetResponseWithData(kExampleDataForecast)))
      .WillOnce(Return(GetResponseWithData(kExampleDataBaseOdessa)));
  EXPECT_EQ(weather.GetTomorrowDiff("Odessa"), "The weather in Odessa tomorrow will be the same than today.");
}

TEST_F(WeatherTestCase, AllDiffTypes) {
  constexpr float kTomorrowTemperature[] = {13.2, 10.2, 9.2, 8.5, 3.};
  constexpr float kTodayTemperature = 9.5;
  const std::string ExpectedString[] = {"much warmer", "warmer", "the same", "colder", "much colder"};
  StrictMock<WeatherMockWithTemperature> weather;
  auto &expect_call = EXPECT_CALL(weather, GetTomorrowTemperature).Times(5);
  for (auto tomorrow_temperature: kTomorrowTemperature) {
    expect_call.WillOnce(Return(tomorrow_temperature));
  }
  EXPECT_CALL(weather, GetTemperature).Times(5).WillRepeatedly(Return(kTodayTemperature));
  for (const auto &expected: ExpectedString) {
    EXPECT_EQ(weather.GetTomorrowDiff("Odessa"), "The weather in Odessa tomorrow will be " + expected + " than today.");
  }
}