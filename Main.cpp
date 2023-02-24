#include<iostream>
#include<bits/stdc++.h>
using namespace std;


unordered_map<string,int> value_map;
vector<int> scores(4,0);
int suit_selected_player = -1;
struct player_info
{
    vector<string> cards;
    vector<string> extra_cards;
};
struct player_info player_detail[4];
void right_rotate(vector<string> &ds)
{
    string prev = ds[0];
    for(int i=1;i<ds.size();i++)
    {
        string temp = ds[i];
        ds[i] = prev;
        prev = temp;
    }
    ds[0] = prev;
}


void shuffle(vector<string> &cards)
{
    vector<string> d1,d2;
    for(int i=0;i<24;i++)
    {
        if(i<12)
        d1.push_back(cards[i]);
        else
        d2.push_back(cards[i]);
    }
    for(int i=0;i<7;i++)
    {
        right_rotate(d1);
        right_rotate(d2);
    }
    vector<string> temp;
    for(auto x:d1)
    temp.push_back(x);
    for(auto x:d2)
    temp.push_back(x);
    cards = temp;
}

int accept_trump(string card)
{
    int accept_p1 = rand() % 2;
    if(accept_p1%2)
    return 1;
    int accept_p2 = rand() % 2;
    if(accept_p2)
    return 2;
    int accept_p3 = rand() % 2;
    if(accept_p3)
    return 3;
    int accept_p4 = rand() % 2;
    if(accept_p4)
    return 4;
    return 0;
}

string get_new_trump()
{
    int ub = 4,lb = 1;
    int random_suit = rand() % (ub - lb + 1);
    if(random_suit==1)
    return "Clubs";
    else if(random_suit==2)
    return "Diamonds";
    else if(random_suit==3)
    return "Hearts";
    return "Spades";
}



void order_cards(string a,string b)
{
    vector<string> dvalue = {"Ace of Diamonds","King of Diamonds","Queen of Diamonds","Jack of Diamonds","Ten of Diamonds","Nine of Diamonds"};
    vector<string> cvalue = {"Ace of Clubs","King of Clubs","Queen of Clubs","Jack of Clubs","Ten of Clubs","Nine of Clubs"};
    vector<string> hvalue = {"Ace of Hearts","King of Hearts","Queen of Hearts","Jack of Hearts","Ten of Hearts","Nine of Hearts"};
    vector<string> svalue = {"Ace of Spades","King of Spades","Queen of Spades","Jack of Spades","Ten of Spades","Nine of Spades"};
    if(a=="Diamonds" && b=="Hearts")
    {
        value_map["Jack of Diamonds"] = 1;
        value_map["Jack of Hearts"] = 2;
        int count = 3;
        for(auto x:dvalue)
        {
            if(x!="Jack of Diamonds")
            value_map[x] = count++;
        }
        for(auto x:cvalue)
        {
            value_map[x] = count++;
        }
        for(auto x:hvalue)
        {
            if(x!="Jack of Hearts")
            value_map[x] = count++;
        }
        for(auto x:svalue)
        {
            value_map[x] = count++;
        }
    }
    else if(a=="Clubs" && b=="Spades")
    {
        value_map["Jack of Clubs"] = 1;
        value_map["Jack of Spades"] = 2;
        int count = 3;
        for(auto x:dvalue)
        {
            value_map[x] = count++;
        }
        for(auto x:cvalue)
        {
            if(x!="Jack of Clubs")
            value_map[x] = count++;
        }
        for(auto x:hvalue)
        {
            value_map[x] = count++;
        }
        for(auto x:svalue)
        {
            if(x!="Jack of Spades")
            value_map[x] = count++;
        }
    }
    else if(a=="Hearts" && b=="Diamonds")
    {
        value_map["Jack of Hearts"] = 1;
        value_map["Jack of Diamonds"] = 2;
        int count = 3;
        for(auto x:dvalue)
        {
            if(x!="Jack of Diamonds")
            value_map[x] = count++;
        }
        for(auto x:cvalue)
        {
            value_map[x] = count++;
        }
        for(auto x:hvalue)
        {
            if(x!="Jack of Hearts")
            value_map[x] = count++;
        }
        for(auto x:svalue)
        {
            value_map[x] = count++;
        }
    }
    else if(a=="Spades" && b=="Clubs")
    {
        value_map["Jack of Spades"] = 1;
        value_map["Jack of Clubs"] = 2;
        int count = 3;
        for(auto x:dvalue)
        {
            value_map[x] = count++;
        }
        for(auto x:cvalue)
        {
            if(x!="Jack of Clubs")
            value_map[x] = count++;
        }
        for(auto x:hvalue)
        {
            value_map[x] = count++;
        }
        for(auto x:svalue)
        {
            if(x!="Jack of Spades")
            value_map[x] = count++;
        }
    }
}

void change_value_for_cards(string suit)
{
    string suit_of_card = "";
    string temp = "";
    for(int i=0;i<suit.size();i++)
    {
        int j = i;
        temp = "";
        while(suit[j]!=' ' && j<suit.size())
        {
            temp+=suit[j];
            j++;
        }
        if(suit_of_card.size()==0)
        suit_of_card += temp;
        else
        suit_of_card = temp + " " + suit_of_card;
        i = j;
    }
    temp = suit_of_card;
    suit_of_card = "";
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i]==' ')
        break;
        suit_of_card += temp[i];    
    }
    cout<<"Trump suit is:"<<suit_of_card<<endl;
    if(suit_of_card=="Diamonds"){
        order_cards("Diamonds","Hearts");
    }
    else if(suit_of_card=="Clubs"){
        order_cards("Clubs","Spades");
    }
    else if(suit_of_card=="Hearts"){
        order_cards("Hearts","Diamonds");
    }
    else if(suit_of_card=="Spades"){
        order_cards("Spades","Clubs");
    }
}

void first_assign(vector<string> cards)
{
    for(int i=0;i<3;i++)
    player_detail[0].cards.push_back(cards[i]);
    for(int i=3;i<5;i++)
    player_detail[1].cards.push_back(cards[i]);
    for(int i=5;i<8;i++)
    player_detail[2].cards.push_back(cards[i]);
    for(int i=8;i<10;i++)
    player_detail[3].cards.push_back(cards[i]);
}

void second_assign(vector<string> cards)
{
    for(int i=10;i<12;i++)
    player_detail[0].cards.push_back(cards[i]);
    for(int i=12;i<15;i++)
    player_detail[1].cards.push_back(cards[i]);
    for(int i=15;i<17;i++)
    player_detail[2].cards.push_back(cards[i]);
    for(int i=17;i<20;i++)
    player_detail[3].cards.push_back(cards[i]);
}

void display_card_to_user()
{
    cout<<"Cards available with you:"<<endl;
    vector<string> cards_with_user = player_detail[0].cards;
    for(auto x:cards_with_user)
    cout<<x<<endl;
    cout<<"Enter the card which you need to play with(Preferably the card of same suit):"<<endl;
    return;
}

bool is_same_suit(string card,string suit)
{
    string temp = "";
    string rev = "";
    for(int i=0;i<card.size();i++)
    {
        int j = i;
        temp = "";
        while(card[j]!=' ' && j<card.size())
        {
            temp+=card[j];
            j++;
        }
        if(rev.size()==0)
        rev += temp;
        else
        rev = temp + " " + rev;
        i = j;
    }
    temp = rev;
    rev = "";
    string s1 = "",s2="";
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i]== ' ')
        break;
        s1 += temp[i];
    }
    temp = "";
    for(int i=0;i<suit.size();i++)
    {
        int j = i;
        temp = "";
        while(suit[j]!=' ' && j<suit.size())
        {
            temp+=suit[j];
            j++;
        }
        if(rev.size()==0)
        rev += temp;
        else
        rev = temp + " " + rev;
        i = j;
    }
    temp = rev;
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i]== ' ')
        break;
        s2 += temp[i];
    }
    if(s1==s2)
    return true;
    return false;
}

string get_card(int player_no,bool flag,string start_suit = "")
{
    if(flag && start_suit.size())
    {
        vector<string> ds;
        for(auto x:player_detail[player_no].cards)
        {
            if(is_same_suit(x,start_suit))
            ds.push_back(x);
        }
        if(ds.size())
        {
            int size = ds.size();
            int random = rand() % size;
            string card_from_cpu = ds[random];
            int index = -1;
            for(int i=0;i<player_detail[player_no].cards.size();i++)
            {
                if(player_detail[player_no].cards[i] == card_from_cpu)
                {
                    index = i;
                    break;
                }
            }
            auto it = player_detail[player_no].cards.begin() + index;
            player_detail[player_no].cards.erase(it);
            cout<<"Card from the player "<<player_no+1<<" is "<<card_from_cpu<<endl;
            return card_from_cpu;
        }
    }
    int size = player_detail[player_no].cards.size();
    int random = rand() % size;
    string card_from_cpu = player_detail[player_no].cards[random];
    auto index = player_detail[player_no].cards.begin() + random;
    player_detail[player_no].cards.erase(index);
    cout<<"Card from the player "<<player_no+1<<" is "<<card_from_cpu<<endl;
    return card_from_cpu;
}

void remove_card_from_user(string card)
{
    int index = -1;
    vector<string> ds = player_detail[0].cards;
    for(int i=0;i<ds.size();i++)
    {
        if(ds[i]==card)
        {
            index = i;
            break;
        }
    }
    auto it = player_detail[0].cards.begin() + index;
    player_detail[0].cards.erase(it);
}

int trick_won(vector<string> cards_from_players)
{
    string card1 = cards_from_players[0];
    string card2 = cards_from_players[1];
    string card3 = cards_from_players[2];
    string card4 = cards_from_players[3];
    int value1 = value_map[card1];
    int value2 = value_map[card2];
    int value3 = value_map[card3];
    int value4 = value_map[card4];
    if(value1 < value2 && value1 < value3 && value1 < value4)
    return 0;
    else if(value2 < value1 && value2 < value3 && value2 < value4)
    return 1;
    else if(value3 < value1 && value3 < value2 && value3 < value4)
    return 2;
    return 3;
}

void resize_cards(int player_no,vector<string> cards)
{
    for(auto x:cards)
    {
        player_detail[player_no].extra_cards.push_back(x);
    }
    return;
}

void calculate_score()
{
    int team1 = 0,team2 = 0;
    for(int i=0;i<4;i++)
    {
        if(i%2==0)
        team1 += scores[i];
        else
        team2 += scores[i];
    }
    if(suit_selected_player==1 || suit_selected_player==3)
    {
        if(team1 <= 3)
        team1 *= 1;
        else
        team1 *= 2;
        if(team2<=3)
        team2 *= 2;
        else
        team2 *= 4;
    }
    else
    {
        if(team2 <= 3)
        team2 *= 1;
        else
        team2 *= 2;
        if(team1<=3)
        team1 *= 2;
        else
        team1 *= 4;
    }
    cout<<endl<<"The Score for Team 1(1 and 3) is:"<<team1<<endl<<"The Score for Team 2(2 and 4) is:"<<team2<<endl;
}

void begin_game(int dealer)
{
    int count1 = player_detail[0].cards.size();
    int count2 = player_detail[1].cards.size();
    int count3 = player_detail[2].cards.size();
    int count4 = player_detail[3].cards.size();
    int turn = (dealer + 1)%4;
    int count = 0;
    while(count1 && count2 && count3 && count4)
    {
        vector<string> cards_from_players(4);
        int temp = turn;
        if(turn==0)
            {
                if(player_detail[0].cards.size()==0)
                {
                    cout<<"You dont have any cards"<<endl;
                }
                else{
                    string card_from_user = "";
                    display_card_to_user();
                    getline(cin,card_from_user,'\n');
                    cout<<"Card put into play is:"<<card_from_user<<endl;
                    cards_from_players[0] = card_from_user;
                    remove_card_from_user(card_from_user);
                }
            }
        else if(player_detail[turn].cards.size()!=0){
        cout<<"Turn for the player:"<<turn+1<<endl;
        cards_from_players[turn] = get_card(turn,false);
        }
        string start_suit = cards_from_players[turn];
        turn++;
        turn = turn % 4;
        while(turn != temp)
        {
            cout<<"Turn for the player:"<<turn+1<<endl;
            if(turn==0)
            {
                if(player_detail[0].cards.size()==0)
                {
                    cout<<"You dont have any cards"<<endl;
                }
                else{
                    string card_from_user = "";
                    display_card_to_user();
                    getline(cin,card_from_user,'\n');
                    cout<<"Card put into play is:"<<card_from_user<<endl;
                    cards_from_players[0] = card_from_user;
                    remove_card_from_user(card_from_user);
                }
            }
            else if(player_detail[turn].cards.size()!=0)
            cards_from_players[turn] = get_card(turn,true,start_suit);
            turn++;
            turn = turn % 4;
        }
        cout<<endl<<"Cards on the floor are"<<endl;
        for(auto x:cards_from_players)
        cout<<x<<endl;
        cout<<endl;
        int win_player = trick_won(cards_from_players);
        cout<<endl<<"Trick won by the player:"<<win_player+1<<endl;
        resize_cards(win_player,cards_from_players);
        count1 = player_detail[0].cards.size();
        count2 = player_detail[1].cards.size();
        count3 = player_detail[2].cards.size();
        count4 = player_detail[3].cards.size();
        turn = win_player;
        scores[win_player] += 1;
    }
    calculate_score();
}

int main()
{
    vector<string> cards = {
        "Nine of Spades",
        "Ten of Spades",
        "Jack of Spades",
        "Queen of Spades",
        "King of Spades",
        "Ace of Spades",
        "Nine of Hearts",
        "Ten of Hearts",
        "Jack of Hearts",
        "Queen of Hearts",
        "King of Hearts",
        "Ace of Hearts",
        "Nine of Clubs",
        "Ten of Clubs",
        "Jack of Clubs",
        "Queen of Clubs",
        "King of Clubs",
        "Ace of Clubs",
        "Nine of Diamonds",
        "Ten of Diamonds",
        "Jack of Diamonds",
        "Queen of Diamonds",
        "King of Diamonds",
        "Ace of Diamonds",
    };
    vector<string> rem_cards;
    shuffle(cards);
    first_assign(cards);
    second_assign(cards);
    for(int i=20;i<24;i++)
    rem_cards.push_back(cards[i]);
    string trump_card = rem_cards[0];
    cout<<endl<<"First card from the remaining card is:"<<trump_card<<endl<<endl<<endl;;
    int accept = accept_trump(trump_card);
    if(accept)
    {
        cout<<"Player "<<accept<<" accepts the first card from the remaining as the trump card"<<endl;
        suit_selected_player = accept-1;
        change_value_for_cards(trump_card);
        begin_game(0);
    }
    else
    {
        string new_selection = get_new_trump();
        cout<<"New choosen trump suit is:"<<new_selection<<endl;
        change_value_for_cards(new_selection);
        begin_game(0);
    }
}
