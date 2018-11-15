#include "addressbook.hpp"
using namespace eosio;
using namespace std;

namespace aaa {

    void addressbook::myaction() {
        addressbook::address_index addresses(_self, _self.value);  // code, scope
        // add to table, first argument is account to bill for storage
        addresses.emplace(_self, [&](auto &address) {
            address.account_name = "dan"_n.value;
            address.first_name = "Daniel";
            address.last_name = "Larimer";
            address.street = "1 EOS Way";
            address.city = "Blacksburg";
            address.state = "VA";
            address.zip = 93446;
        });
        addresses.emplace(_self, [&](auto &address) {
                address.account_name = "baobao"_n.value;
                address.first_name = "Jackie";
                address.last_name = "Chen";
                address.street = "1 Bei Way";
                address.city = "Hong Kong";
                address.state = "Hong Kong";
                address.zip = 93446;
            });
        uint32_t zipnumb = 93446;
        auto zip_index = addresses.get_index<name("zip")>();
        auto itr = zip_index.find(zipnumb);
//        if(itr != zip_index.end()){
                eosio::print("itr->account_name: ", uint_to_string(itr->account_name));  // 仅会显示Jackie Chen    
//        }
        eosio_assert(itr->account_name == name("dan").value, "Lock arf, Incorrect Record ");
    }



/**
 * 将 name 转化为 字符串
 * @param name uint64_t的name
 */
    std::string addressbook::uint_to_string(const uint64_t name) const
    {
            static const char *charmap = ".12345abcdefghijklmnopqrstuvwxyz";

            std::string str(13, '.');

            uint64_t tmp = name;
            for (uint32_t i = 0; i <= 12; ++i)
            {
                    char c = charmap[tmp & (i == 0 ? 0x0f : 0x1f)];
                    str[12 - i] = c;
                    tmp >>= (i == 0 ? 4 : 5);
            }

            const auto last = str.find_last_not_of('.');
            if (last != std::string::npos)
                    str = str.substr(0, last + 1);
            return str;
    }

    EOSIO_DISPATCH(addressbook, (myaction))

}
