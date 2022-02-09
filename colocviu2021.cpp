/* Toader Vlad - Marian - grupa 142
Tutore laborator: Szemeteanca Eduard
Compilator: Codeblocks, GNU GCC Compiler */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class malware{
protected:
    float rating;
    int data_infectare[3];
    string nume;
    string metoda_infectare;
    vector<string> reg_modif;
public:
    malware();
    float get_rating(){return this->rating;}
    malware(int zi, int luna, int an, string nume,
            vector<string> reg_modif, string metoda_infectare);
    malware(const malware&m);
    malware& operator=(const malware&m);
    friend ostream& operator<<(ostream& out, const malware&m);
    virtual ostream& afisare(ostream& out) const; //afisare virtuala
    virtual void calcul_rating()=0; //metoda virtuala pura de a calcula ratingul
    virtual ~malware();
};
ostream& malware::afisare(ostream& out) const
{
    out<<"Rating: "<<this->rating<<'\n';
    out<<"Data infectare: "<<this->data_infectare[0]<<'/'<<this->data_infectare[1]<<'/'<<this->data_infectare[2]<<'\n';
    out<<"Nume: "<<this->nume<<'\n';
    out<<"Metoda infectare: "<<this->metoda_infectare<<'\n';
    out<<"Registri modificati: ";
    for (int i=0;i<this->reg_modif.size();++i)
        out<<this->reg_modif[i]<<" ";
    out<<'\n';
    return out;
}
ostream& operator<<(ostream& out, const malware&m) //operator << in care se apeleaza metoda virtuala de afisare
{
    return m.afisare(out);
}
malware::malware()
{
    this->rating=0;
    this->data_infectare[0]=0;
    this->data_infectare[1]=0;
    this->data_infectare[2]=0;
    this->nume="-";
    this->metoda_infectare="unknown";
}
malware::malware(int zi, int luna, int an, string nume,
                 vector <string> reg_modif, string metoda_infectare="unknown")
{
    this->data_infectare[0]=zi;
    this->data_infectare[1]=luna;
    this->data_infectare[2]=an;
    this->nume=nume;
    this->metoda_infectare=metoda_infectare;
    for (int i=0;i<reg_modif.size();++i)
        this->reg_modif.push_back(reg_modif[i]);
}
malware::malware(const malware&m)
{
    this->rating=m.rating;
    this->data_infectare[0]=m.data_infectare[0];
    this->data_infectare[1]=m.data_infectare[1];
    this->data_infectare[2]=m.data_infectare[2];
    this->nume=m.nume;
    this->metoda_infectare=m.metoda_infectare;
    for (int i=0;i<m.reg_modif.size();++i)
        this->reg_modif.push_back(m.reg_modif[i]);
}
malware::~malware()
{
    if (this->reg_modif.empty())
        this->reg_modif.clear();
}
malware& malware::operator=(const malware&m)
{
    if (this!=&m)
    {
        if (this->reg_modif.empty())
            this->reg_modif.clear();
        this->rating=m.rating;
        this->data_infectare[0]=m.data_infectare[0];
        this->data_infectare[1]=m.data_infectare[1];
        this->data_infectare[2]=m.data_infectare[2];
        this->nume=m.nume;
        this->metoda_infectare=m.metoda_infectare;
        for (int i=0;i<m.reg_modif.size();++i)
            this->reg_modif.push_back(m.reg_modif[i]);
    }
    return *this;
}

class rootkit: public virtual malware{ //mostenire virtuala pentru diamant
protected:
    vector<string> importuri;
    vector<string> stringuri_semnificative;
public:
    rootkit();
    rootkit(int zi, int luna, int an, string nume, vector<string> reg_modif,
            vector<string> importuri, vector<string> stringuri_semnificative, string metoda_infectare);
    rootkit(const rootkit&r);
    rootkit& operator=(const rootkit&r);
    ostream& afisare(ostream& out) const;
    void calcul_rating();
    ~rootkit();
};
void rootkit::calcul_rating()  //suprascrierea metodei virtuale de calcul rating
{
    this->rating=0;
    for (int i=0;i<this->stringuri_semnificative.size();++i)
        if (this->stringuri_semnificative[i]=="“System Service Descriptor Table" ||
            this->stringuri_semnificative[i]=="SSDT" || this->stringuri_semnificative[i]=="“NtCreateFile")
            this->rating=this->rating+100;
    for (int i=0;i<this->importuri.size();++i)
        if (this->importuri[i]=="ntoskrnl.exe")
            this->rating=this->rating*2;
    for (int i=0;i<this->reg_modif.size();++i)
        if (this->reg_modif[i]=="HKLM-run"||this->reg_modif[i]=="HKCU-run")
            this->rating=this->rating+20;
}
ostream& rootkit::afisare(ostream& out) const //suprascrierea metodei virtuale de afisare
{
    malware::afisare(out);
    out<<"Importuri: ";
    for (int i=0;i<this->importuri.size();++i)
        out<<this->importuri[i]<<" ";
    out<<'\n';
    out<<"Stringuri semnificative: ";
    for (int i=0;i<this->stringuri_semnificative.size();++i)
        out<<this->stringuri_semnificative[i]<<" ";
    out<<'\n';
    return out;
}
rootkit::rootkit():malware()
{

}
rootkit::rootkit(int zi, int luna, int an, string nume, vector<string> reg_modif,
            vector<string> importuri, vector<string> stringuri_semnificative,
            string metoda_infectare="unknown"): malware(zi,luna,an,nume,reg_modif,metoda_infectare)
{
    for (int i=0;i<importuri.size();++i)
        this->importuri.push_back(importuri[i]);
    for (int i=0;i<stringuri_semnificative.size();++i)
        this->stringuri_semnificative.push_back(stringuri_semnificative[i]);
    rootkit::calcul_rating();
}
rootkit::rootkit(const rootkit&r):malware(r)
{
    for (int i=0;i<r.importuri.size();++i)
        this->importuri.push_back(r.importuri[i]);
    for (int i=0;i<r.stringuri_semnificative.size();++i)
        this->stringuri_semnificative.push_back(r.stringuri_semnificative[i]);
}
rootkit::~rootkit()
{
    if (this->importuri.empty())
        this->importuri.clear();
    if (this->stringuri_semnificative.empty())
        this->stringuri_semnificative.clear();
}
rootkit& rootkit::operator=(const rootkit&r)
{
    if (this!=&r)
    {
        malware::operator=(r);
        if (this->importuri.empty())
            this->importuri.clear();
        if (this->stringuri_semnificative.empty())
            this->stringuri_semnificative.clear();
        for (int i=0;i<r.importuri.size();++i)
            this->importuri.push_back(r.importuri[i]);
        for (int i=0;i<r.stringuri_semnificative.size();++i)
            this->stringuri_semnificative.push_back(r.stringuri_semnificative[i]);
    }
    return *this;
}
class keylogger: public virtual malware{ //mostenire virtuala pentru diamant
protected:
    vector<string> functii;
    vector<string> taste_speciale;
public:
    keylogger();
    keylogger(int zi, int luna, int an, string nume, vector<string> reg_modif,
            vector<string> functii, vector<string> taste_speciale, string metoda_infectare);
    keylogger(const keylogger&r);
    keylogger& operator=(const keylogger&r);
    ostream& afisare(ostream& out) const;
    void calcul_rating();
    ~keylogger();
};
void keylogger::calcul_rating() //suprascrierea metodei virtuale de calcul al ratingului
{
    this->rating=0;
    for (int i=0;i<this->functii.size();++i)
        if (this->functii[i]=="CreateFileW"||this->functii[i]=="OpenProcess"||this->functii[i]=="ReadFile"||
            this->functii[i]=="WriteFile"||this->functii[i]=="RegisterHotKey"||this->functii[i]=="SetWindowsHookEx")
                this->rating=this->rating+30;
    for (int i=0;i<this->taste_speciale.size();++i)
        if (this->taste_speciale[i]=="[Up]"||this->taste_speciale[i]=="[Num Lock]"||this->taste_speciale[i]=="[Down]"||
            this->taste_speciale[i]=="[Right]"||this->taste_speciale[i]=="[UP]"||this->taste_speciale[i]=="[Left]"||
            this->taste_speciale[i]=="[PageDown]")
                this->rating=this->rating+10;
    for (int i=0;i<this->reg_modif.size();++i)
        if (this->reg_modif[i]=="HKLM-run"||this->reg_modif[i]=="HKCU-run")
            this->rating=this->rating+20;
}
ostream& keylogger::afisare(ostream& out) const //suprascrierea metodei virtuale de afisare
{
    malware::afisare(out);
    out<<"Functii: ";
    for (int i=0;i<this->functii.size();++i)
        out<<this->functii[i]<<" ";
    out<<'\n';
    out<<"Taste speciale: ";
    for (int i=0;i<this->taste_speciale.size();++i)
        out<<this->taste_speciale[i]<<" ";
    out<<'\n';
    return out;
}
keylogger::keylogger():malware()
{
}
keylogger::keylogger(int zi, int luna, int an, string nume, vector<string> reg_modif,
            vector<string> functii, vector<string> taste_speciale,
            string metoda_infectare="unknown"): malware(zi,luna,an,nume,reg_modif,metoda_infectare)
{
    for (int i=0;i<functii.size();++i)
        this->functii.push_back(functii[i]);
    for (int i=0;i<taste_speciale.size();++i)
        this->taste_speciale.push_back(taste_speciale[i]);
    keylogger::calcul_rating();
}
keylogger::keylogger(const keylogger&r):malware(r)
{
    for (int i=0;i<r.functii.size();++i)
        this->functii.push_back(r.functii[i]);
    for (int i=0;i<r.taste_speciale.size();++i)
        this->taste_speciale.push_back(r.taste_speciale[i]);
}
keylogger::~keylogger()
{
    if (this->functii.empty())
        this->functii.clear();
    if (this->taste_speciale.empty())
        this->taste_speciale.clear();
}
keylogger& keylogger::operator=(const keylogger&r)
{
    if (this!=&r)
    {
        malware::operator=(r);
        if (this->functii.empty())
            this->functii.clear();
        if (this->taste_speciale.empty())
            this->taste_speciale.clear();
        for (int i=0;i<r.functii.size();++i)
            this->functii.push_back(r.functii[i]);
        for (int i=0;i<r.taste_speciale.size();++i)
            this->taste_speciale.push_back(r.taste_speciale[i]);
    }
    return *this;
}
class kernel_keylogger: public virtual rootkit, public virtual keylogger{ //mostenire in diamant
private:
    bool ascunde_fisiere;
    bool ascunde_registri;
public:
    kernel_keylogger();
    kernel_keylogger(int zi, int luna, int an, string nume, vector<string> reg_modif,
            vector<string> importuri, vector<string> stringuri_semnificative, vector<string> functii,
            vector<string> taste_speciale, bool ascunde_fisiere, bool ascunde_registri,
            string metoda_infectare);
    kernel_keylogger(const kernel_keylogger&k);
    ostream& afisare(ostream& out) const;
    kernel_keylogger& operator=(const kernel_keylogger&k);
    void calcul_rating();
    ~kernel_keylogger();
};
void kernel_keylogger::calcul_rating() //suprascrierea metodei virtuale de calcul al ratingului
{
    this->rating=0;
    rootkit::calcul_rating();
    keylogger::calcul_rating();
    if (this->ascunde_fisiere==1)
        this->rating=this->rating+20;
    if (this->ascunde_registri==1)
        this->rating=this->rating+30;
    for (int i=0;i<this->reg_modif.size();++i)
        if (this->reg_modif[i]=="HKLM-run"||this->reg_modif[i]=="HKCU-run")
            this->rating=this->rating+20;
}
ostream& kernel_keylogger::afisare(ostream& out) const //suprascrierea metodei virtuale de afisare
{
    malware::afisare(out);
    out<<"Importuri: ";
    for (int i=0;i<this->importuri.size();++i)
        out<<this->importuri[i]<<" ";
    out<<'\n';
    out<<"Stringuri semnificative: ";
    for (int i=0;i<this->stringuri_semnificative.size();++i)
        out<<this->stringuri_semnificative[i]<<" ";
    out<<'\n';
    out<<"Functii: ";
    for (int i=0;i<this->functii.size();++i)
        out<<this->functii[i]<<" ";
    out<<'\n';
    out<<"Taste speciale: ";
    for (int i=0;i<this->taste_speciale.size();++i)
        out<<this->taste_speciale[i]<<" ";
    out<<"Ascunde fisiere? (1-DA, 0-NU): "<<this->ascunde_fisiere<<'\n';
    out<<"Ascunde registri? (1-DA, 0-NU): "<<this->ascunde_registri<<'\n';
    out<<'\n';
}
kernel_keylogger::kernel_keylogger():malware(),rootkit(),keylogger()
{
    this->ascunde_fisiere=0;
    this->ascunde_registri=0;
}
kernel_keylogger::kernel_keylogger(int zi, int luna, int an, string nume,
        vector<string> reg_modif, vector<string> importuri, vector<string> stringuri_semnificative,
        vector<string> functii, vector<string> taste_speciale, bool ascunde_fisiere, bool ascunde_registri,
        string metoda_infectare="unknown"):malware(zi,luna,an,nume,reg_modif,metoda_infectare),
        rootkit(zi,luna,an,nume,reg_modif,importuri,stringuri_semnificative,metoda_infectare),
        keylogger(zi,luna,an,nume,reg_modif,functii,taste_speciale,metoda_infectare)
{
    this->ascunde_fisiere=ascunde_fisiere;
    this->ascunde_registri=ascunde_registri;
    kernel_keylogger::calcul_rating();
}
kernel_keylogger::kernel_keylogger(const kernel_keylogger&k):malware(k),rootkit(k),keylogger(k)
{
    this->ascunde_fisiere=k.ascunde_fisiere;
    this->ascunde_registri=k.ascunde_registri;
}
kernel_keylogger& kernel_keylogger::operator=(const kernel_keylogger&k)
{
    if (this!=&k)
    {
        malware::operator=(k);
        if (this->importuri.empty())
            this->importuri.clear();
        if (this->stringuri_semnificative.empty())
            this->stringuri_semnificative.clear();
        for (int i=0;i<k.importuri.size();++i)
            this->importuri.push_back(k.importuri[i]);
        for (int i=0;i<k.stringuri_semnificative.size();++i)
            this->stringuri_semnificative.push_back(k.stringuri_semnificative[i]);
        if (this->functii.empty())
            this->functii.clear();
        if (this->taste_speciale.empty())
            this->taste_speciale.clear();
        for (int i=0;i<k.functii.size();++i)
            this->functii.push_back(k.functii[i]);
        for (int i=0;i<k.taste_speciale.size();++i)
            this->taste_speciale.push_back(k.taste_speciale[i]);
        this->ascunde_fisiere=k.ascunde_fisiere;
        this->ascunde_registri=k.ascunde_registri;
    }
    return *this;
}
kernel_keylogger::~kernel_keylogger()
{
}

class ransomware: public malware{
private:
    int rating_criptare;
    float rating_obfuscare;
public:
    ransomware();
    ransomware(int zi, int luna, int an, string nume, vector<string> reg_modif,
            int rating_criptare, float rating_obfuscare, string metoda_infectare);
    ransomware(const ransomware&r);
    ransomware& operator=(const ransomware&r);
    void calcul_rating();
    ostream& afisare(ostream& out) const;
    ~ransomware();
};
void ransomware::calcul_rating() //suprascrierea metodei virtuale de calcul al ratingului
{
    this->rating=this->rating_criptare+this->rating_obfuscare;
    for (int i=0;i<this->reg_modif.size();++i)
        if (this->reg_modif[i]=="HKLM-run"||this->reg_modif[i]=="HKCU-run")
            this->rating=this->rating+20;
}
ostream& ransomware::afisare(ostream& out) const //suprascrierea metodei virtuale de afisare
{
    malware::afisare(out);
    out<<"Rating criptate: "<<this->rating_criptare<<'\n';
    out<<"Rating obfuscare: "<<this->rating_obfuscare<<'\n';
    return out;
}
ransomware::ransomware():malware()
{
    this->rating_criptare=0;
    this->rating_obfuscare=0;
}
ransomware::ransomware(int zi, int luna, int an, string nume, vector<string> reg_modif,
            int rating_criptare, float rating_obfuscare, string metoda_infectare="unknown"):malware(zi,luna,an,nume,reg_modif,metoda_infectare)
{
    this->rating_criptare=rating_criptare;
    this->rating_obfuscare=rating_obfuscare;
    ransomware::calcul_rating();
}
ransomware::ransomware(const ransomware&r):malware(r)
{
    this->rating_criptare=r.rating_criptare;
    this->rating_obfuscare=r.rating_obfuscare;
}
ransomware& ransomware::operator=(const ransomware&r)
{
    if (this!=&r)
    {
        malware::operator=(r);
        this->rating_criptare=r.rating_criptare;
        this->rating_obfuscare=r.rating_obfuscare;
    }
    return *this;
}
ransomware::~ransomware()
{
}

class computer{
private:
    const int id;
    static int contor_id;
    vector <malware*> malwares;
    float rating_final;
public:
    computer(vector<malware*>malwares);
    computer();
    float get_rating_final(){return this->rating_final;}
    bool operator>(const computer&c);
    computer(const computer&c);
    computer& operator=(const computer&c);
    friend ostream& operator<<(ostream& out, const computer&c);
    void calcul_rating_final();
    ~computer();
};
bool computer::operator>(const computer&c) //pentru sortare
{
    if (this->rating_final>c.rating_final)
        return 1;
    return 0;
}
void computer::calcul_rating_final()
{
    this->rating_final=0;
    for (int i=0;i<this->malwares.size();++i)
        this->rating_final=this->rating_final+this->malwares[i]->get_rating();
}
ostream& operator<<(ostream& out, const computer&c)
{
    out<<"Id computer: "<<c.id<<'\n';
    out<<"Numar malwares: "<<c.malwares.size()<<"\n\n";
    for (int i=0;i<c.malwares.size();++i)
        out<<*c.malwares[i];
    out<<"Rating final: "<<c.rating_final<<'\n';
    return out;
}
int computer::contor_id=0;
computer::computer():id(++contor_id)
{
    this->rating_final=0;
}
computer::computer(vector <malware*>malwares):id(++contor_id)
{
    for (int i=0;i<malwares.size();++i)
        this->malwares.push_back(malwares[i]);
    computer::calcul_rating_final();
}
computer::computer(const computer&c): id(++contor_id)
{
    for (int i=0;i<c.malwares.size();++i)
        this->malwares.push_back(c.malwares[i]);
    this->rating_final=c.rating_final;
}
computer::~computer()
{
    if (this->malwares.empty())
        this->malwares.clear();
}
computer& computer::operator=(const computer&c)
{
    if (this!=&c)
    {
        if (this->malwares.empty())
            this->malwares.clear();
        for (int i=0;i<c.malwares.size();++i)
            this->malwares.push_back(c.malwares[i]);
        this->rating_final=c.rating_final;
    }
}
template <class tip_clasa1> //functie template pentru a schimba 2 valori (pentru a sorta vectorul de computere)
void t_swap(tip_clasa1 &a1, tip_clasa1 &a2)
{
  tip_clasa1 aux;
  aux=a1;
  a1=a2;
  a2=aux;
}
class meniu{ // singletone - model preluat din laboratorul dl. tutore Szmeteanca Eduard
private:                    // (pentru a exemplifica conceptul de singletone - design pattern)
    static meniu* ob;
    meniu()
    {
    }
public:
    static meniu* get_menu()
    {
        if (ob==NULL)
            ob=new meniu();
        return ob;
    }
    void run()
    {
        vector <string> stringuri;
        stringuri.push_back("SSDT");
        stringuri.push_back("NtCreateFile");
        vector <string> importuri;
        importuri.push_back("ntoskrnl.exe");
        vector <string> importuri1;
        importuri1.push_back("chrome.exe");
        vector <string> reg;
        reg.push_back("HKLM-run");
        reg.push_back("HKCU-run");
        vector <string> reg1;
        reg1.push_back("HKLT-run");
        vector <string> taste;
        taste.push_back("[UP]");
        taste.push_back("[Num Lock]");
        vector <string> taste1;
        taste1.push_back("[Ctrl]");
        vector <string> functii;
        functii.push_back("ReadFile");
        functii.push_back("WriteFile");
        vector <string> functii1;
        functii1.push_back("ReadFile");
        functii1.push_back("UploadFile");
        malware *m1=new rootkit(29,5,2021,"Rootkit 1",reg,importuri,stringuri);
        malware *m2=new keylogger(28,5,2021,"Keylogger 1",reg1,functii,taste,"email");
        malware *m3=new kernel_keylogger(26,5,2021,"Kernel keylogger 1",reg,importuri1,stringuri,functii1,taste1,1,1);
        malware *m4=new ransomware(25,5,2021,"Ransomware 1",reg,17,46.5);
        vector <malware*> malwares1;
        malwares1.push_back(m1);
        malwares1.push_back(m2);
        malwares1.push_back(m3);
        vector <malware*>malwares2;
        malwares2.push_back(m1);
        malwares2.push_back(m4);
        computer *c1=new computer();
        computer *c2=new computer(malwares1);
        computer *c3=new computer(malwares2);
        vector <computer*> computere;
        computere.push_back(c1);
        computere.push_back(c2);
        computere.push_back(c3);

        int op=0;
        while (op!=5)
        {
            cout<<"\n\n1. afisarea informatiilor pentru fiecare calculator\n";
            cout<<"2. afisarea informatiilor pentru fiecare calculator ordonate dupa rating\n";
            cout<<"3. afisarea primilor k calculatoare ordonate dupa rating\n";
            cout<<"4. afisarea procentului de computere infectate\n";
            cout<<"5. iesire\n";
            cout<<"OPTIUNE=";
            cin>>op;
            if (op==1)
            {
                for (int i=0;i<computere.size();++i)
                    cout<<*computere[i]<<"\n-------------\n";
            }
            else if (op==2)
            {
                vector <computer*> computer_sort;
                computer_sort=computere;
                for (int i=0;i<computer_sort.size()-1;++i)
                    for (int j=i+1;j<computer_sort.size();++j)
                        if (*computer_sort[i]>*computer_sort[j])
                            t_swap(*computer_sort[i],*computer_sort[j]);
                for (int i=0;i<computer_sort.size();++i)
                    cout<<*computer_sort[i]<<"\n-------------\n";
            }
            else if (op==3)
            {
                cout<<"Introduceti k! (numar calculatoare = "<<computere.size()<<")\n";
                int k;
                cin>>k;
                if (k>computere.size())
                    throw runtime_error("k introdus este mai mare decat numarul de calculatoare!");
                else
                {
                    vector <computer*> computer_sort;
                    computer_sort=computere;
                    for (int i=0;i<computer_sort.size()-1;++i)
                        for (int j=i+1;j<computer_sort.size();++j)
                            if (*computer_sort[i]>*computer_sort[j])
                                t_swap(*computer_sort[i],*computer_sort[j]);
                    for (int i=0;i<k;++i)
                        cout<<*computer_sort[i]<"\n-------------\n";
                }
            }
            else if (op==4)
            {
                int nr_comp_inf=0;
                for (int i=0;i<computere.size();++i)
                    if (computere[i]->get_rating_final()>0)
                        ++nr_comp_inf;
                if (computere.size()>0)
                    cout<<((float)nr_comp_inf/computere.size())*100<<"% calculatoare infectate";
            }
            else if (op==5)
                break;
            else throw runtime_error("Optiunea aleasa nu exista!");
        }
    }
};
meniu *meniu::ob=NULL;
int main()
{
    try {
        meniu *menu=menu->get_menu();
        menu->run();
    }
    catch (exception &e){ //daca se prinde o exceptie se afiseaza mesajul intors de aceasta
        cout<<"Am prins o exceptie - "<<e.what()<<'\n';
    }
    return 0;
}
