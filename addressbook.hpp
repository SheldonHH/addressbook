#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/singleton.hpp>
using namespace eosio;
using namespace std;
namespace  aaa {
    class [[eosio::contract("addressbook")]] addressbook : public contract {

    public:
        addressbook(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds) {}


        struct [[eosio::table, eosio::contract("addressbook")]] address {
            uint64_t account_name;
            string first_name;
            string last_name;
            string street;
            string city;
            string state;
            uint32_t zip = 0;

            uint64_t primary_key() const { return account_name; }

            uint64_t by_zip() const { return zip; }
        };

        typedef eosio::multi_index<name("address"), address,
                indexed_by < name("zip"), const_mem_fun < address, uint64_t, &address::by_zip> >>
        address_index;

        [[eosio::action]]
        void myaction();

        std::string uint_to_string(const uint64_t name) const;
    };

}
