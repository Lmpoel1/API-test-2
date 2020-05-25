#include <cpprest/http_client.h>
#include <cpprest/json.h>
//#pragma comment(lib, "cpprest_2_10")

using namespace web;
using namespace web::http;
using namespace web::http::client;

#include <iostream>
using namespace std;

void display_json(
    json::value const& jvalue,
    utility::string_t const& prefix)
{
    wcout << prefix << jvalue.serialize() << endl;

}

pplx::task<http_response> make_task_request(
    http_client& client,
    method mtd,
    json::value const& jvalue)
{
    return (mtd == methods::GET || mtd == methods::HEAD) ?
        client.request(mtd, L"/restdemo") :
        client.request(mtd, L"/restdemo", jvalue);
}

void make_request(
    http_client& client,
    method mtd,
    json::value const& jvalue)
{
    make_task_request(client, mtd, jvalue)
        .then([](http_response response)
    {
        if (response.status_code() == status_codes::OK)
        {
            return response.extract_json();
        }
        return pplx::task_from_result(json::value());
    })
        .then([](pplx::task<json::value> previousTask)
    {
        try
        {
            display_json(previousTask.get(), L"R: ");
        }
        catch (http_exception const& e)
        {
            wcout << e.what() << endl;
        }
    })
        .wait();
}

int main()
{
    http_client client(U("http://10.211.55.9/smartgrid"));

    auto putvalue1 = json::value::object();
    putvalue1[L"object"] = json::value::string(L"group");
    putvalue1[L"operation"] = json::value::string(L"add");
    putvalue1[L"data"][L"name"] = json::value::string(L"group 1");
    putvalue1[L"data"][L"waitTime"] = json::value::number(NULL);
    wcout << L"\nPUT (add values)\n";
    display_json(putvalue1, L"S: ");
    make_request(client, methods::PUT, putvalue1);

    auto putvalue2 = json::value::object();
    putvalue2[L"object"] = json::value::string(L"module");
    putvalue2[L"operation"] = json::value::string(L"add");
    putvalue2[L"data"][L"id"] = json::value::number(3);
    putvalue2[L"data"][L"moduleType"] = json::value::string(L"DUZA");
    putvalue2[L"data"][L"name"] = json::value::string(L"Zonnenpanneel");
    putvalue2[L"data"][L"adress"] = json::value::string(L"DUZA1"); 
    putvalue2[L"data"][L"groupID"] = json::value::number(0);
    wcout << L"\nPUT (add values)\n";
    display_json(putvalue2, L"S: ");
    make_request(client, methods::PUT, putvalue2);

    //TODO show reqest group and module

    auto putvalue5 = json::value::object();
    putvalue5[L"object"] = json::value::string(L"group");
    putvalue5[L"operation"] = json::value::string(L"update");
    putvalue5[L"data"][L"id"] = json::value::number(3);
    putvalue5[L"data"][L"name"] = json::value::string(L"");
    putvalue5[L"data"][L"waitTime"] = json::value::number(5);
    wcout << L"\nPUT (add values)\n";
    display_json(putvalue5, L"S: ");
    make_request(client, methods::PUT, putvalue5);


    auto putvalue3 = json::value::object();
    putvalue3[L"object"] = json::value::string(L"group");
    putvalue3[L"operation"] = json::value::string(L"update");
    putvalue3[L"data"][L"id"] = json::value::number(3);
    putvalue3[L"data"][L"name"] = json::value::string(L"group 1 new");
    putvalue3[L"data"][L"waitTime"] = json::value::number(20);
    wcout << L"\nPUT (add values)\n";
    display_json(putvalue3, L"S: ");
    make_request(client, methods::PUT, putvalue3);

    auto putvalue4 = json::value::object();
    putvalue4[L"object"] = json::value::string(L"group");
    putvalue4[L"operation"] = json::value::string(L"update");
    putvalue4[L"data"][L"id"] = json::value::number(1);
    putvalue4[L"data"][L"name"] = json::value::string(L"");
    putvalue4[L"data"][L"waitTime"] = json::value::number(5);
    wcout << L"\nPUT (add values)\n";
    display_json(putvalue4, L"S: ");
    make_request(client, methods::PUT, putvalue4);


    auto putvalue6 = json::value::object();
    putvalue6[L"object"] = json::value::string(L"module");
    putvalue6[L"operation"] = json::value::string(L"update");
    putvalue6[L"data"][L"id"] = json::value::number(1);
    putvalue6[L"data"][L"moduleType"] = json::value::string(L"DUZA");
    putvalue6[L"data"][L"name"] = json::value::string(L"Zonnenpanneel");
    putvalue6[L"data"][L"adress"] = json::value::string(L"");
    putvalue6[L"data"][L"groupID"] = json::value::number(1);
    wcout << L"\nPUT (add values)\n";
    display_json(putvalue6, L"S: ");
    make_request(client, methods::PUT, putvalue6);
    
    auto nullvalue = json::value::null();

    
   
   
    auto getvalue1 = json::value::object();
    getvalue1[L"object"] = json::value::string(L"module");
    getvalue1[L"operation"] = json::value::string(L"all");
    getvalue1[L"data"][L"id"] = json::value::number(1);
     wcout << L"\nGET (get  values test)\n";
    display_json(getvalue1, L"S: ");
    make_request(client, methods::POST, getvalue1);

    auto getvalue2 = json::value::object();
    getvalue2[L"object"] = json::value::string(L"group");
    getvalue2[L"operation"] = json::value::string(L"single");
    getvalue2[L"data"][L"id"] = json::value::number(1);
    wcout << L"\nGET (get  values test)\n";
    display_json(getvalue2, L"S: ");
    make_request(client, methods::POST, getvalue2);


   /* wcout << L"\nGET (get  values test)\n";
    display_json(nullvalue, L"S: ");
    make_request(client, methods::GET, nullvalue);

    /* auto getvalue = json::value::array();
    getvalue[0] = json::value::string(L"one");
    getvalue[1] = json::value::string(L"two");
    getvalue[2] = json::value::string(L"three");

    wcout << L"\nPOST (get some values)\n";
    display_json(getvalue, L"S: ");
    make_request(client, methods::POST, getvalue);

    auto delvalue = json::value::array();
    delvalue[0] = json::value::string(L"one");

    wcout << L"\nDELETE (delete values)\n";
    display_json(delvalue, L"S: ");
    make_request(client, methods::DEL, delvalue);

    wcout << L"\nPOST (get some values)\n";
    display_json(getvalue, L"S: ");
    make_request(client, methods::POST, getvalue);

    auto nullvalue = json::value::null();

    wcout << L"\nGET (get all values)\n";
    display_json(nullvalue, L"S: ");
    make_request(client, methods::GET, nullvalue);

    return 0; */
}