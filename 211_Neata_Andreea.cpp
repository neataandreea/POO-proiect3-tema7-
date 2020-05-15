#include <iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<typeinfo>
#include<windows.h>


using namespace std;

class date
{
    int zi;
    int luna;
    int an;
public:
    date(int, int, int);
    date();
    virtual ~date();
    virtual void citire(istream & in);
    virtual void afisare(ostream & out);
    friend istream & operator >>(istream &, date&);
    friend ostream &operator<<(ostream &, date &);
    date &operator=(const date&);
    date (const date&);
    friend class cont_bancar;
    template<class cont_economii> friend class GestionareConturi;
    int get_year()
    {
        return an;
    }
    int get_month()
    {
        return luna;
    }
    int get_day()
    {
        return zi;
    }
};

duration_calculator(date d1, date d2)
{
    int dif_ani=d2.get_year()-d1.get_year();
    int dif_luni= dif_ani*12;
    if(d2.get_month()>d1.get_month())
        dif_luni=dif_luni+(d2.get_month()-d1.get_month());
    if(d2.get_month()<d1.get_month())
        dif_luni=dif_luni-(d1.get_month()-d2.get_month()+1);
    if(d2.get_month()==d1.get_month() && d2.get_day()<d1.get_day())
        dif_luni--;
    return dif_luni;

}

date::date(const date &ob)
{
    this->zi=ob.zi;
    this->luna=ob.luna;
    this->an=ob.an;
}

date &date::operator=(const date&ob)
{

    if(this!=&ob)
    {
        this->zi=ob.zi;
        this->luna=ob.luna;
        this->an=ob.an;
        return *this;
    }
}
date::date()
{
    zi=0;
    luna=0;
    an=0;
}
date::date(int day, int month, int year)
{
    try
    {
        if(day<1||day>31)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Introduceti o zi a lunii valida constructor\n";
        exit(EXIT_FAILURE);
    }
    zi=day;
    try
    {
        if(month<1||month>12)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Introduceti o luna a anului valida\n";
        exit(EXIT_FAILURE);
    }
    luna=month;
    try
    {
        if(year<1000||year>9999)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Valoarea introdusa pentru an nu este valida\n";
        exit(EXIT_FAILURE);
    }
    an=year;
}
date::~date() {}
void date::citire(istream &in)
{
    int day, month, year;
    cout<<"ziua:";
    in>>day;
    try
    {
        if(day<1||day>31)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Introduceti o zi a lunii valida\n";
        exit(EXIT_FAILURE);
    }
    cout<<"luna:";
    in>>month;
    try
    {
        if(month<1||month>12)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Introduceti o luna a anului valida\n";
        exit(EXIT_FAILURE);
    }
    cout<<"an:";
    in>>year;
    try
    {
        if(year<1000||year>9999)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Valoarea introdusa pentru an nu este valida\n";
        exit(EXIT_FAILURE);
    }
    zi=day;
    luna=month;
    an=year;

}
void date::afisare(ostream &out)
{
    if (zi<10)
        out<<'0'<<zi<<"-";
    else
        out<<zi<<"-";
    if(luna<10)
        out<<'0'<<luna<<"-";
    else
        out<<luna<<"-";
    out<<an<<endl;
}
istream &operator >>(istream & in, date & ob)
{
    ob.citire(in);
    return in;
}
ostream &operator<<(ostream &out, date &ob)
{
    ob.afisare(out);
    return out;
}


///-----------------------------------------------------



class cont_bancar
{
    date data;
    string detinator;
    float sold;
    int id_cont;
public:
    cont_bancar(string, date,float,int,int);
    virtual void citire(istream &in);
    virtual void afisare(ostream & out);
    friend istream &operator >>(istream &, cont_bancar&);
    friend ostream & operator<<(ostream &, cont_bancar&);
    ~cont_bancar();
    cont_bancar (const cont_bancar&);
    cont_bancar &operator=(const cont_bancar&);
    void set_sold(float);
    const float get_sold();
    const int get_id_cont();

    date get_data()
    {
        return data;
    }
};

const int cont_bancar::get_id_cont()
{
    return id_cont;
}
void cont_bancar::set_sold(float s)
{
    sold=s;
}
const float cont_bancar::get_sold()
{
    return (sold);
}
cont_bancar::cont_bancar(const cont_bancar&ob)
{
    this->detinator=ob.detinator;
    this->data=ob.data;
    this->sold=ob.sold;
    this->id_cont=ob.id_cont;
}
cont_bancar &cont_bancar ::operator=(const cont_bancar &ob)
{
    if(this!=&ob)
    {
        this->detinator=ob.detinator;
        this->data=ob.data;
        this->sold=ob.sold;
        this->id_cont=ob.id_cont;
        return *this;
    }
}
cont_bancar::~cont_bancar() {}
void cont_bancar::afisare(ostream&out)
{
    out <<"id_cont:"<<id_cont<<endl;
    out<<"nume detinator:"<<detinator<<endl;
    out<<"data:"<<data;
    out<<"sold:"<<sold<<endl;
}
void cont_bancar :: citire(istream & in)
{
    cout<<"nume detinator:";
    string nume,buf;
    getline(in,buf);
    getline(in,nume);
    detinator=nume;
    cout<<"id_cont:";
    int id;
    in>>id;
    id_cont=id;
    cout<<"data:";
    date d;
    in>>d;
    data=d;
    cout<<"sold:";
    float s;
    in >>s;
    sold=s;
}
istream &operator >>(istream & in, cont_bancar &ob)
{
    ob.citire(in);
    return in;
}
date dd;
cont_bancar::cont_bancar( string client="",date d=dd,float s=0, int id=0, int tranz=0)
{
    detinator=client;
    data=d;
    sold=s;
    id_cont=id;
}
ostream &operator<<(ostream &out, cont_bancar &ob)
{
    ob.afisare(out);
    return out;
}



///--------------------------------------------------------


class dob
{
    int perioada;
    float rata;
public:
    dob (int, float);
    dob();
    virtual ~dob();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream & operator>>(istream&,dob&);
    friend ostream &operator<<(ostream &, dob&);
    dob(const dob &);
    dob &operator=(const dob &);
    friend class cont_economii;
};
dob&dob::operator=(const dob&ob)
{
    if(this!=&ob)
    {
        this->perioada=ob.perioada;
        this->rata=ob.rata;
        return *this;
    }
}
dob::dob(const dob &ob)
{
    this->perioada=ob.perioada;
    this->rata=ob.rata;
}
dob::dob()
{
    perioada=0;
    rata=0;
}
dob::dob(int p, float r)
{
    try
    {
        if(p!=3 || p!=6 || p!=12)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Rata dobanzii poate fi pe o perioada de 3,6 sau 12 luni\n";
        exit(EXIT_FAILURE);
    }
    perioada=p;
    rata=r;
}
dob::~dob() {}
void dob::citire(istream &in)
{
    cout<<"perioada:";
    int p;
    in>>p;
    try
    {
        if(p!=3 && p!=6 && p!=12)
            throw 1;
    }
    catch(int i)
    {
        cout<<"Rata dobanzii poate fi pe o perioada de 3,6 sau 12 luni\n";
        exit(EXIT_FAILURE);
    }
    perioada=p;
    cout<<"rata:";
    float r;
    in>>r;
    rata=r;
}
void dob::afisare(ostream &out)
{
    out<<"perioada:"<<perioada<<endl;
    out<<"rata:"<<rata<<endl;
}
istream &operator >>(istream & in, dob & ob)
{
    ob.citire(in);
    return in;
}
ostream &operator <<(ostream & out, dob & ob)
{
    ob.afisare(out);
    return out;
}


///-------------------------------------------------------------------------------------------------------------------


template<class cont> class GestionareConturi ;
///-----------------------------------------------------------------------------------------------------------------------
class operatiune
{
    int retragere;
    int depunere;
    bool interogare;
public:
    operatiune(int r, int d, bool i);
    ~operatiune ();
    void afisare(ostream &out);
    friend ostream & operator << (ostream &, operatiune&);
    void citire(istream &in);
    friend istream & operator >>(istream &, operatiune&);
    friend bool operator ==(operatiune&, operatiune&);
    friend bool operator !=(operatiune&, operatiune&);
    template<class cont> friend class GestionareConturi;
    friend class cont_economii;
};

bool operator !=(operatiune &ob1,operatiune&ob2)
{
    return !(ob1==ob2);
}
bool operator ==(operatiune&ob1,operatiune&ob2)
{
    return(ob1.retragere==ob2.retragere && ob1.depunere==ob2.depunere && ob1.interogare==ob2.interogare);
}

void operatiune ::citire(istream &in)
{
    cout<<"suma retrasa:";
    in>>retragere;
    cout<<"suma depusa:";
    in>>depunere;
    cout<<"interogare sold: ";
    in>>interogare;

}
istream &operator>>(istream &in, operatiune &ob)
{
    ob.citire(in);
    return in;
}
ostream &operator<<(ostream & out, operatiune &ob)
{
    ob.afisare(out);
    return out;
}
void operatiune::afisare(ostream &out)
{
    out<<"retragere:"<<retragere<<endl;
    out<<"depunere:"<<depunere<<endl;
    out<<"interogare sold :"<<interogare<<endl;

}
operatiune::~operatiune() {}
operatiune::operatiune(int r=0, int d=0, bool i=0)
{
    retragere=r;
    depunere=d;
    interogare=i;
}
//vector<operatiune>t;
//unordered_map<int, vector<operatiune>> f;


///-----------------------------------------------------------------------------------------------------------------------


class cont_economii:virtual public cont_bancar
{
protected:
    vector<float> istoric;
    dob dobanda;
public:
    cont_economii(string, date, float,int,dob);
    ~cont_economii();
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream & operator>>(istream &, cont_economii&);
    friend ostream & operator<<(ostream &, cont_economii&);
    cont_economii(const cont_economii&);
    cont_economii &operator=(const cont_economii&);
    void set_istoric(float s)
    {
        istoric.push_back(s);
    }
    int get_dob()
    {
        return dobanda.perioada;
    }
    float get_rata_pe_luna()
    {
        return dobanda.rata/dobanda.perioada;
    }

};
cont_economii &cont_economii::operator =(const cont_economii&ob)
{
    if(this!=&ob)
    {
        this->cont_bancar::operator=(ob);
        this->istoric=ob.istoric;
        this->dobanda=ob.dobanda;
        return *this;
    }
}
cont_economii::cont_economii(const cont_economii& ob):cont_bancar(ob)
{
    this->istoric=ob.istoric;
    this->dobanda=ob.dobanda;
}
dob dobb;
cont_economii::cont_economii( string client="",date ddd=dd,float s=0, int id=0,dob d=dobb)
    :cont_bancar(client,ddd,s,id)
{
    dobanda=d;

}
cont_economii::~cont_economii() {}
void cont_economii::citire(istream&in)
{
    cont_bancar::citire(in);
    dob d;
    in>>d;
    dobanda=d;

}
void cont_economii::afisare(ostream &out)
{
    cont_bancar::afisare(out);
    out<<"dobanda:"<<dobanda;
    out<<"istoric:"<<endl;
    int j=1;
    vector<float>::iterator i;
    for (i=istoric.begin(); i<istoric.end(); ++i)
    {
        out<<"sold in urma tranzactiei "<<j<<":"<<(*i)<<endl;
        j++;
    }
}
istream & operator>>(istream &in, cont_economii & ob)
{
    ob.citire(in);
    return in;
}
ostream & operator<<(ostream &out, cont_economii &ob)
{
    ob.afisare(out);
    return out;
}


///---------------------------------------------------------------------------------------------------------------------------


class cont_curent:virtual public cont_bancar
{
    int tranzactii_gratuite;
public:
    cont_curent(string, date, float,int,int);
    ~cont_curent();
    cont_curent(const cont_curent&);
    cont_curent &operator=(const cont_curent&);
    void afisare(ostream & out);
    void citire(istream &in);
    friend istream &operator >>(istream &in, cont_curent&);
    friend ostream &operator<<(ostream &out, cont_curent&);
    void set_tranzactii(int nr_nou)
    {
        tranzactii_gratuite=nr_nou;
    }
    int get_tranzactii()
    {
        return tranzactii_gratuite;
    }
};
istream &operator >>(istream &in, cont_curent&ob)
{
    ob.citire(in);
    return in;
}
ostream &operator<<(ostream &out, cont_curent&ob)
{
    ob.afisare(out);
    return out;
}

void cont_curent::afisare(ostream &out)
{
    cont_bancar::afisare(out);
    out<<"numar tranzactii gratuite: ";
    out<<tranzactii_gratuite;
}
void cont_curent::citire(istream &in)
{
    cont_bancar::citire(in);
    cout<<"Introduceti numarul de tranzactii gratuite pentru acest cont: ";
    int tr;
    in>>tr;
    tranzactii_gratuite=tr;
}
cont_curent::cont_curent(string client="",date ddd=dd,float s=0, int id=0,int tr=0)
    :cont_bancar(client,ddd,s,id)
{
    tranzactii_gratuite=tr;
}
cont_curent::~cont_curent() {}
cont_curent::cont_curent(const cont_curent&ob):cont_bancar(ob)
{
    this->tranzactii_gratuite=ob.tranzactii_gratuite;
}
cont_curent&cont_curent::operator=(const cont_curent&ob)
{
    if(this!=&ob)
    {
        this->cont_bancar::operator=(ob);
        this->tranzactii_gratuite=ob.tranzactii_gratuite;
        return *this;
    }
}


///------------------------------------------------------------------------------------------------------------------------


template<class cont> class GestionareConturi
{
    vector <cont> conturi;
    vector<operatiune>operatiuni;
    unordered_map<int, vector<operatiune>> gestiune;
    static int index;
public:


    GestionareConturi() {}
    GestionareConturi(vector<operatiune> op, unordered_map<int,vector<operatiune>> gest)
    {
        operatiuni=op;
        gestiune=gest;
        index+=1;
    }
    GestionareConturi(const GestionareConturi& ob)
    {
        this->conturi=ob.conturi;
        this->operatiuni=ob.operatiuni;
        this->gestiune=ob.gestiune;
        index+=1;
    }
    GestionareConturi &operator=(const GestionareConturi&ob)
    {
        if(this!=&ob)
        {
            this->conturi=ob.conturi;
            this->operatiuni=ob.operatiuni;
            this->gestiune=ob.gestiune;
            return *this;
        }
    }
    GestionareConturi&operator +=(const GestionareConturi&ob)
    {
        gestiune.insert({ob.get_id_cont(),ob.operatiuni});

    }
    ~GestionareConturi() {}
    void citire(istream &in);
    friend istream & operator>>(istream &in, GestionareConturi <cont>&ob)
    {
        ob.citire(in);
        return in;
    }
    void afisare (ostream &out);

    friend ostream &operator<<(ostream &out, GestionareConturi<cont>&ob)
    {
        ob.afisare(out);
        return out;
    }
    void retragere_numerar();
    void depunere_numerar();
    void interogare_sold();
    void retragere_alta_banca();
    void plata_online();
    static void nr_conturi()
    {
        cout<<index;
    }
 void add_cont(cont_curent & c)
    {
        gestiune.insert({c.get_id_cont(),operatiuni});
        index+=1;
        conturi.push_back(c);
    }
};

template <class cont>
int GestionareConturi<cont>::index;


template<class cont>
void GestionareConturi<cont>::interogare_sold()
{
    cout<<"Introduceti id-ul contului";
    int cod;
    cin>>cod;
    auto it=gestiune.find(cod);
    if(it!=gestiune.end())
    {
        typename vector<cont>::iterator i;
        for (i=conturi.begin(); i<conturi.end(); ++i)
            if((*i).get_id_cont()==cod)
                cout<<"Suma curenta: "<<(*i).get_sold()<<endl;
    }
    operatiune o;
    o.interogare=1;
    operatiuni.push_back(o);
    gestiune.erase(gestiune.find(cod));
    gestiune.insert({cod, operatiuni});
}

template<class cont>
void GestionareConturi<cont>::plata_online()
{
    cout<<"Introduceti id-ul contului";
    int cod;
    cin>>cod;

    auto it=gestiune.find(cod);
    if(it!=gestiune.end())
    {

        typename  vector <cont> :: iterator i;
        for (i=conturi.begin(); i<conturi.end(); ++i)
            if ((*i).get_id_cont()==cod)
            {
                if((*i).get_tranzactii()==0)
                {
                    cout<<"Pentru plati online se percepe un cost suplimentar de 4 lei.Doriti sa continuati?(1/0)";
                    bool raspuns;
                    cin>>raspuns;
                    if(raspuns)
                    {
                        float suma;
                        cout<<"Suma pe care vreti sa o platiti:";
                        cin>>suma;
                        float suma_noua=(*i).get_sold();
                        suma_noua=suma_noua-(suma+4);
                        (*i).set_sold(suma_noua);
                    }

                }
                else
                {

                    float suma;
                    cout<<"Suma pe care vreti sa o platiti:";
                    cin>>suma;
                    float suma_noua=(*i).get_sold();
                    suma_noua=suma_noua-(suma+4);
                    (*i).set_sold(suma_noua);
                    (*i).set_tranzactii((*i).get_tranzactii()-1);
                }
                gestiune.erase(gestiune.find(cod));
                gestiune.insert({cod, operatiuni});
            }
    }
    else
        cout<<"Cont inexistent";

}



template<class cont>
void GestionareConturi<cont>::depunere_numerar()
{
    cout<<"Introduceti id-ul contului";
    int cod;
    cin>>cod;
    cout<<"Ce suma doriti sa depuneti?";
    float suma;
    cin>>suma;
    operatiune o;
    o.retragere=suma;
    operatiuni.push_back(o);
    auto it=gestiune.find(cod);
    if(it!=gestiune.end())
    {

        typename        vector <cont> :: iterator i;
        for (i=conturi.begin(); i<conturi.end(); ++i)
            if ((*i).get_id_cont()==cod)
            {
                float suma_noua=(*i).get_sold();
                suma_noua=suma_noua+suma;
                (*i).set_sold(suma_noua);
            }
    }
    else
        cout<<"Cont inexistent";
    gestiune.erase(gestiune.find(cod));
    gestiune.insert({cod, operatiuni});
}

template<class cont>
void GestionareConturi<cont>::retragere_alta_banca()
{
    cout<<"Introduceti id-ul contului";
    int cod;
    cin>>cod;
    auto it=gestiune.find(cod);
    if(it!=gestiune.end())
    {
        typename        vector<cont>::iterator i;
        for (i=conturi.begin(); i<conturi.end(); ++i)
            if ((*i).get_id_cont()==cod )

            {
                if ((*i).get_tranzactii()==0)
                {
                    cout<<"Tranzactia aleasa nu este gratuita. Costul acesteia este de 5 ron.Continuati retragerea?(1/0)";
                    bool raspuns;
                    cin>>raspuns;
                    if(raspuns)
                    {
                        cout<<"Ce suma doriti sa retrageti?";
                        float suma;
                        cin>>suma;
                        try
                        {
                            if(suma>(*i).get_sold())
                                throw 1;
                        }
                        catch(int i)
                        {
                            cout<<"Sold insuficient\n";
                            exit(EXIT_FAILURE);
                        }
                        operatiune o;
                        o.retragere=suma;
                        operatiuni.push_back(o);
                        float suma_noua=(*i).get_sold();
                        suma_noua=suma_noua-suma-5;
                        (*i).set_sold(suma_noua);
                    }
                }
                else
                {
                    cout<<"Ce suma doriti sa retrageti?";
                    float suma;
                    cin>>suma;
                    try
                    {
                        if(suma>(*i).get_sold())
                            throw 1;
                    }
                    catch(int i)
                    {
                        cout<<"Sold insuficient\n";
                        exit(EXIT_FAILURE);
                    }
                    operatiune o;
                    o.retragere=suma;
                    operatiuni.push_back(o);
                    float suma_noua=(*i).get_sold();
                    suma_noua=suma_noua-suma;
                    (*i).set_sold(suma_noua);
                    (*i).set_tranzactii((*i).get_tranzactii()-1);
                }
                gestiune.erase(gestiune.find(cod));
                gestiune.insert({cod, operatiuni});
            }

    }
    else
        cout<<"Cont inexistent.";


}

template<class cont>
void GestionareConturi<cont>::retragere_numerar()
{
    cout<<"Introduceti id-ul contului";
    int cod;
    cin>>cod;


    auto it=gestiune.find(cod);
    if(it!=gestiune.end())
    {

        typename        vector <cont> :: iterator i;
        for (i=conturi.begin(); i<conturi.end(); ++i)
            if ((*i).get_id_cont()==cod)
            {
                cout<<"Ce suma doriti sa retrageti?";
                float suma;
                cin>>suma;
                try
                {
                    if(suma>(*i).get_sold())
                        throw 1;
                }
                catch(int i)
                {
                    cout<<"Sold insuficient\n";
                    exit(EXIT_FAILURE);
                }
                float suma_noua=(*i).get_sold();
                suma_noua=suma_noua-suma;
                (*i).set_sold(suma_noua);
                operatiune o;
                o.retragere=suma;
                operatiuni.push_back(o);
            }

    }
    else
        cout<<"Cont inexistent";
    gestiune.erase(gestiune.find(cod));
    gestiune.insert({cod, operatiuni});
}
template<class cont>
void GestionareConturi<cont>::citire(istream &in)
{
    cont c;
    in>>c;
    conturi.push_back(c);
    int cod;
    cod=c.get_id_cont();
    gestiune.insert({cod,operatiuni});

    index+=1;
}

template<class cont>
void GestionareConturi<cont>::afisare(ostream &out)
{

    for (auto& x: gestiune)
    {
        int cod=x.first;
        typename            vector<cont>::iterator i;
        for (i=conturi.begin(); i<conturi.end(); ++i)
        {
            if((*i).get_id_cont()==cod)
                cout<<(*i);

        }
        cout<<endl;
    }

}


///------------------------------------------------------------------------------------------------------


template<>
class GestionareConturi<cont_economii>
{
    vector <cont_economii> conturi;
    vector<operatiune>operatiuni;
    unordered_map<int, vector<operatiune>> gestiune;
    //static date ultima_actualizare;
    static int index2;
public:
    void add_cont(cont_economii &c)
    {
        gestiune.insert({c.get_id_cont(),operatiuni});
        index2+=1;
        conturi.push_back(c);
    }
    void afisare_dobanda_1an()
    {
        for (auto& x: gestiune)
        {
            vector<cont_economii>::iterator i;
            for(i=conturi.begin(); i<conturi.end(); ++i)
                if((*i).get_id_cont()==x.first && (*i).get_dob()==12)
                {
                    cout<<(*i)<<endl;
                }
        }
    }
    GestionareConturi(){}
    GestionareConturi(vector<operatiune>op, unordered_map<int,vector<operatiune>> gest )
    {
        index2+=1;
        operatiuni=op;
        gestiune=gest;
    }
    GestionareConturi(const GestionareConturi& ob)
    {
        index2+=1;
        this->conturi=ob.conturi;
        this->operatiuni=ob.operatiuni;
        this->gestiune=ob.gestiune;

    }
    GestionareConturi &operator=(const GestionareConturi&ob)
    {
        if(this!=&ob)
        {
            this->conturi=ob.conturi;
            this->operatiuni=ob.operatiuni;
            this->gestiune=ob.gestiune;
            return *this;
        }
    }
    ~GestionareConturi() {}

    void citire(istream &in)
    {
        cont_economii c;
        in>>c;
        int cod=c.get_id_cont();

        int durata;
        SYSTEMTIME x;
        GetSystemTime(&x);
        date data_azi(x.wDay,x.wMonth,x.wYear);
        durata=duration_calculator(c.get_data(),data_azi);
        c.set_sold(c.get_sold()+(durata*c.get_rata_pe_luna()*c.get_sold()));
        conturi.push_back(c);
        gestiune.insert({cod,operatiuni});
        index2+=1;
    }


    friend istream & operator>>(istream &in, GestionareConturi <cont_economii>&ob)
    {
        ob.citire(in);
        return in;
    }

    void afisare (ostream &out)
    {
        for (auto& x: gestiune)
        {
            int cod=x.first;
            typename            vector<cont_economii>::iterator i;
            for (i=conturi.begin(); i<conturi.end(); ++i)
            {
                if((*i).get_id_cont()==cod)
                    cout<<(*i);
            }
            cout<<endl;
        }
    }

    friend ostream &operator<<(ostream &out, GestionareConturi<cont_economii>&ob)
    {
        ob.afisare(out);
        return out;
    }
    void retragere_numerar()
    {
        cout<<"Introduceti id-ul contului";
        int cod;
        cin>>cod;
        cout<<"Ce suma doriti sa retrageti?";

        auto it=gestiune.find(cod);
        if(it!=gestiune.end())
        {

            vector <cont_economii> :: iterator i;
            for (i=conturi.begin(); i<conturi.end(); ++i)
                if ((*i).get_id_cont()==cod)
                {
                    float suma;
                    cin>>suma;
                    try
                    {
                        if(suma>(*i).get_sold())
                            throw 1;
                    }
                    catch(int i)
                    {
                        cout<<"Sold insuficient\n";
                        exit(EXIT_FAILURE);
                    }
                    operatiune o;
                    o.retragere=suma;
                    operatiuni.clear();
                    operatiuni.push_back(o);
                    float suma_noua=(*i).get_sold();
                    suma_noua=suma_noua-suma;
                    (*i).set_sold(suma_noua);
                    (*i).set_istoric(suma_noua);

                }
        }
        else
            cout<<"Cont inexistent";
        gestiune.erase(gestiune.find(cod));
        gestiune.insert({cod, operatiuni});
    }
    void depunere_numerar()
    {
        cout<<"Introduceti id-ul contului";
        int cod;
        cin>>cod;
        cout<<"Ce suma doriti sa depuneti?";
        float suma;
        cin>>suma;
        operatiune o;
        o.depunere=suma;
        operatiuni.push_back(o);
        auto it=gestiune.find(cod);
        if(it!=gestiune.end())
        {

            typename  vector <cont_economii> :: iterator i;
            for (i=conturi.begin(); i<conturi.end(); ++i)
                if ((*i).get_id_cont()==cod)
                {
                    float suma_noua=(*i).get_sold();
                    suma_noua=suma_noua+suma;
                    (*i).set_sold(suma_noua);
                    (*i).set_istoric(suma_noua);
                }

        }
        else
            cout<<"Cont inexistent";
        gestiune.erase(gestiune.find(cod));
        gestiune.insert({cod, operatiuni});
    }


    void interogare_sold()
    {
        cout<<"Introduceti id-ul contului";
        int cod;
        cin>>cod;
        auto it=gestiune.find(cod);
        if(it!=gestiune.end())
        {
            typename vector<cont_economii>::iterator i;
            for (i=conturi.begin(); i<conturi.end(); ++i)
                if((*i).get_id_cont()==cod)
                    cout<<"Suma curenta: "<<(*i).get_sold()<<endl;
        }
        operatiune o;
        o.interogare=1;
        operatiuni.push_back(o);
        gestiune.erase(gestiune.find(cod));
        gestiune.insert({cod, operatiuni});
    }
    static void nr_conturi()
    {
        cout<<index2;
    }
};
//date GestionareConturi<cont_economii>::ultima_actualizare;

int GestionareConturi<cont_economii>::index2;
///---------------------------------------------------------------

void tip(cont_bancar *&cb,int &i)
{
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul contului"<<": ";
    cin>>s;
    try
    {

        if(s=="curent")
        {
            cb=new cont_curent;
            cin>>*cb;
            i++;
        }
        else if(s=="economii")
        {
            cb=new cont_economii;
            cin>>*cb;
            i++;
        }
        else
            throw 10;
    }
    catch (bad_alloc var)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un cont valid. Incercati curent sau economii.\n ";
    }
}

///-----------------------------------------------------------------------------------------------------------------------------

void menu_output()
{
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    printf("1. Citire+ afisare n conturi");
    printf("\n");
    printf("2. Cont curent");
    printf("\n");
    printf("3. Cont economii");
    printf("\n");
    printf("4. Afisare activitate banca ");
    printf("\n");
    printf("0. Iesire.");
    printf("\n");
}
void menu_output_normal()
{
    printf("\n Cont curent: \n");
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    printf("1. Adaugare cont ");
    printf("\n");
    printf("2. Interogare sold ");
    printf("\n");
    printf("3. Retragere numerar ");
    printf("\n");
    printf("4. Retragere numerar-alta banca ");
    printf("\n");
    printf("5. Plata online ");
    printf("\n");
    printf("6.Depunere numerar ");
    printf("\n");
    printf("0. Iesire.");
    printf("\n");
}
void menu_output_economii()
{
    printf("\n Cont economii: \n");
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    printf("1. Adaugare cont economii");
    printf("\n");
    printf("2. Interogare sold ");
    printf("\n");
    printf("3. Retragere numerar ");
    printf("\n");
    printf("4. Depunere numerar");
    printf("\n");
    printf("5. Afisare conturi cu rata dobanzii pe un an");
    printf("\n");
    printf("0. Iesire.");
    printf("\n");
}
void menu()
{
    int option;
    option=0;
    GestionareConturi<cont_curent>c;
    GestionareConturi<cont_economii>g;
    cont_bancar **v;

    do
    {
        menu_output();

        printf("\nIntroduceti numarul actiunii: ");
        scanf("%d", &option);
        if (option==1)
        {
            int n;

            cout<<"Numarul de conturi:";
            cin>>n;
            v=new cont_bancar*[n];
            for(int i=0; i<n;)
                tip(v[i],i);
            for(int i=0; i<n; i++)
            {
                cout<<"\n"<<*v[i]<<endl;
                cout<<"--------------------------\n";
            }
            for(int i=0; i<n; i++)
            {

                cont_curent *p1=dynamic_cast<cont_curent*>(v[i]);

                cont_economii *p2=dynamic_cast<cont_economii*>(v[i]);

                if (p1)
                    c.add_cont(*p1);
                if (p2)
                    g.add_cont(*p2);
            }

        }
        if (option==2)
        {
            int option2=0;

            do
            {
                menu_output_normal();
                printf("\nIntroduceti numarul actiunii: ");
                scanf("%d", &option2);
                if(option2==1)
                    cin>>c;
                if(option2==2)
                    c.interogare_sold();
                if(option2==3)
                    c.retragere_numerar();
                if(option2==4)
                    c.retragere_alta_banca();
                if(option2==5)
                    c.plata_online();
                if(option2==6)
                    c.depunere_numerar();
                if(option2==0)
                    printf("\nEXIT!\n");
                if (option<0||option>6)
                    printf("\nSelectie invalida\n");
                printf("\n");
                system("pause");
                system("cls");

            }
            while(option2!=0);
        }
        if(option==3)
        {
            int option3=0;

            do
            {

                menu_output_economii();
                printf("\nIntroduceti numarul actiunii: ");
                scanf("%d", &option3);
                if(option3==1)
                    cin>>g;
                if(option3==2)
                    g.interogare_sold();
                if(option3==3)
                    g.retragere_numerar();
                if(option3==4)
                    g.depunere_numerar();
                if(option3==5)
                    g.afisare_dobanda_1an();
                if(option3==0)
                    printf("\nEXIT!\n");
                if(option3<0||option3>5)
                    printf("\nSelectie invalida\n");
                printf("\n");
                system("pause");
                system("cls");
            }
            while(option3!=0);


        }
        if(option==4)
        {

            cout<<c;
            cout<<g;
        }
        if (option==0)
        {
            printf("\nEXIT!\n");
        }
        if (option<0||option>4)
        {
            printf("\nSelectie invalida\n");
        }
        printf("\n");
        system("pause");
        system("cls");
    }
    while(option!=0);
}
int main()
{
  menu();

    return 0;
}
