#include <iostream>
#include <string>
using namespace std;
using  std :: cout;
using  std::cin;
class info_settings
{
public:
    const string PRICE_TITLE = "price: ";
    const string DISCOUNT_TITLE = "discount: ";
    const string NAME_TITLE = "name: ";
    const string WIRE_LENGTH_TITLE = "wire length/M: ";
    const string REV_PER_MINUTE_TITLE = "revolutions per minute: ";
    const string POWER_WATT_TITLE = "power/W: ";
    const string POWER_ACC_TITLE = "power type: battery ";
    const string IS_MANUAL_TITLE = "manual: ";
};
class instrument
{
public:
    virtual string get_name() = 0;
    virtual float get_price() = 0;
    virtual uint16_t get_discont() = 0;
protected:
    string name;
    float price;
    int discount;
};
class electric_tool : protected instrument
{
protected:
    int power_watt;
    float wire_length_metr;
    int rev_per_minute; 
    bool have_wire;
public:
    electric_tool(string n, float p, float w_l_m, int p_w = 1600, int r_p = 800, bool h_w = 1, uint16_t di = 0)
    {
        name = n; price = p;
        if (di > 100 || di < 0) {
            throw "The value should not be negative and exceed 100";
        }
        else discount = di;
        power_watt = p_w;
        rev_per_minute = r_p;
        wire_length_metr = w_l_m;
        have_wire = h_w;
    }
    virtual string get_info(electric_tool) { return " "; }
    string get_name() override { return name; }
    uint16_t get_discont() override { return discount; }
    int get_power_watt() { return power_watt; }
    float get_wire_length_metr() { return wire_length_metr; }
    int get_rev_per_minute() { return rev_per_minute; }
    bool is_have_wire() { return have_wire; }

    float get_price() override
    {
        return price - (price / 100) * discount;
    }
};
class drill : public electric_tool
{
public:
    static string get_str() { return "dril"; }
    string get_info(electric_tool d) override
    {
        info_settings inf_sett;
        return type + "\n" + inf_sett.NAME_TITLE + d.get_name() + "\n"
            + inf_sett.PRICE_TITLE + to_string(d.get_price()) + "\n"
            + (d.get_discont() == 0 ? "  " : inf_sett.DISCOUNT_TITLE + to_string(d.get_discont()) + "%" + "\n")
            + inf_sett.POWER_WATT_TITLE + to_string(d.get_power_watt()) + "\n"
            + inf_sett.REV_PER_MINUTE_TITLE + to_string(d.get_rev_per_minute()) + "\n"
            + (d.is_have_wire() ? inf_sett.WIRE_LENGTH_TITLE + to_string(d.get_wire_length_metr()) : inf_sett.POWER_ACC_TITLE);
    }
    drill(string n, float p,float w_l_m,int p_w, int r_p, bool h_w, uint16_t di = 0) 
         : electric_tool(n,p,w_l_m,p_w,r_p,h_w,di) {}
    ~drill() {}
private:
    static string type;
};
class circular : public electric_tool
{
public:
    static string get_str() { return "circ"; }
    bool get_is_manula() { return is_manual; }
    circular(string n, float p, float w_l_m, int p_w, int r_p, bool h_w, bool is_manual, uint16_t di = 0)
        : electric_tool(n, p, w_l_m, p_w, r_p, h_w, di)
    {
        this->is_manual = is_manual;
        have_wire = h_w;
    }
    ~circular() {}
    string get_info(electric_tool d) override
    {
        info_settings inf_sett;
        return type + "\n" + inf_sett.NAME_TITLE + d.get_name() + "\n"
            + inf_sett.PRICE_TITLE + to_string(d.get_price()) + "\n"
            + (d.get_discont() == 0 ? "  " : inf_sett.DISCOUNT_TITLE + to_string(d.get_discont()) + "%" + "\n")
            + inf_sett.POWER_WATT_TITLE + to_string(d.get_power_watt()) + "\n"
            + inf_sett.REV_PER_MINUTE_TITLE + to_string(d.get_rev_per_minute()) + "\n"
            + (d.is_have_wire() ? inf_sett.WIRE_LENGTH_TITLE + to_string(d.get_wire_length_metr()) : inf_sett.POWER_ACC_TITLE) + "\n"
            + (have_wire ? inf_sett.IS_MANUAL_TITLE + "NO" : inf_sett.IS_MANUAL_TITLE + "YES");
    }
private:
   static bool is_manual;
   static string type;
};
bool circular::is_manual;
string circular::type = "-- Circular --";
string drill::type = "-- Dril --";
void print(string str)
{
    cout << str << endl;
    cout << "-----------------------------------------" << endl;
}
void show_menu()
{
    string show_obj_info = "show information about objects: '1'";
    string show_max_price = "show object with max price: 2";
    string return_to_main_menu = "return to main menu: '4'";
    string exit = "exit: '0'";
    print(show_obj_info + "\n" + show_max_price + "\n" + exit + "\n");
}
int get_arg()
{
    int arg;
    cin >> arg;
    return arg;
}
void show_obj_info(electric_tool* el_tools [], int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        print(el_tools[i]->get_info(*(el_tools[i])));
    }
}
electric_tool* max_price(electric_tool* el_tools[], int arr_s)
{
    float curent_price = 0.0;
    int curent_obj = 0;
    for (int i = 0; i < arr_s; i++)
    {
        if (el_tools[i]->get_price() > curent_price) 
        {
            curent_price = el_tools[i]->get_price();
            curent_obj = i;
        }
    }
    return el_tools[curent_obj];
}
void clean_memory(electric_tool* el_tool[], int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        delete el_tool[i];
    }
}
int main()
{  
    const int array_size = 10;
    electric_tool* tools[array_size];

    for (int i = 0; i < array_size; i++)
    {
        int iter = 0;
        iter += i * 100;
        bool is_true = i % 2 == 0 ? 1 : 0;
        i % 2 == 0 ?
            tools[i] = new drill("Bosh -Z" + to_string(i * 10 + i), 1000.00 + iter, 1.5 + 1 / 10, 1600 + iter, 800 + iter, !is_true, 0 + i * 2) :
            tools[i] = new circular("Makita -FE" + to_string(i * 10 + i), 1000.00 + iter, 1.5 + i / 10, 1600 + iter, 800 + iter, is_true, is_true, 0 + i * 2);
    }
    try
    {
        while (true)
        {
            show_menu();
            int ch = get_arg();
            switch (ch)
            {
            case 1:
                show_obj_info(tools, array_size);
                break;
            case 2:
            { electric_tool* el_t = max_price(tools, array_size);
            print(el_t->get_info(*el_t));}
                break;
            case 4:
                show_menu();
                break;
            case 0:
                return 0;
            default:
                throw "UNCORRECT COMAND LINE ARGUMENT!";
                return -1;
            }
        }
    }
    catch (const char* msg)
    {
        print(msg);
    }
    return 0;
}

