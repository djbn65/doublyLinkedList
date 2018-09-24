/* Sample tester
 * We've included std::list below to show you how your types should behave.
 * You can use that for debugging.
 * As in the assignment description, if you use the std::list for your submitted code,
 * you will get a 0.
 * Compile with g++ pa05.cpp BigInteger.cpp -std=c++11
 * Add the -g flag if you want to use GDB like we learned in lab this week.
 */

// USE THIS TO TEST, BUT REMOVE LATER
#include <list>

#include "BigInteger.h"
#include "MyList.h"

int main()
{
    // Make your hpp file with empty definitions other than your constructor
    // Build one function at a time, and only add one "test" line at a time to this file.
    MyList<int> l;

    for (int i = 0; i < 1000; i++)
      l.push_back(i);

    MyList<int> w(l);

    w.reverse();

    for (int i = 0; i < 1000; i++)
    {
      cout << l.back() << endl;
      l.pop_back();
    }

    for (int i = 0; i < 1000; i++)
    {
      cout << w.back() << endl;
      w.pop_back();
    }

    MyList<int> z(w);

    z.pop_back();
    z.erase(-1);

    cout << z.size() << endl;
    z.insert(1,7);
    z.insert(2,8);
    cout << z.size() << endl;
    cout << z.back() << endl;
    MyList<int> a(z);

    a.clear();

    MyList<int> q(a);

    cout << q.size() << endl;

    q.assign(100, 5);

    cout << q.size() << endl;

    for (int i = 0; i < 100; i++)
    {
      cout << q.back() << endl;
      q.pop_back();
    }

    cout << q.size() << endl;

    // Uncommend and add lines below here 1 at a time!

    // Test all your MyList functions here:
    /*cout << l.size() << endl;
    l.push_back(4000);
    l.push_back(200);
    l.push_back(100);
    cout << l.front() << endl;
    cout << l.back() << endl;

    l.push_front(423);

    cout << l.front() << endl;

    MyList<int> sink;
    sink = l;
    MyList<int> sink2(sink);
    cout << sink.front() << endl;
    cout << sink.back() << endl;

    l.insert(l.begin(), 3);
    l.insert(l.end(), 20);
    l.reverse();

    sink2.assign(10,300);
    sink2.remove(300);
    sink2.assign(12,2);
    sink2.resize(3);

    int j = l.size();
    for(auto i = 0; i < j; i++)
    {
        cout << l.back() << endl;
        l.pop_back();
    }

    int t = sink.size();
    for(auto i = 0; i < t; i++)
    {
        cout << sink.back() << endl;
        sink.pop_back();
    }

    int x = sink2.size();
    for(auto i = 0; i < x; i++)
    {
        cout << sink2.back() << endl;
        sink2.pop_back();
    }*/

    // Test all your BigInteger functions here:
    /*std::string init_string("58");
    std::string othr_string("29");

    BigInteger x(init_string);
    BigInteger y(othr_string);
    long long yy = 2;
    long long xx = 5;
    BigInteger w("42759623945362874523475928732590864235");
    BigInteger z("-562345384752945658723493");

    cout << x.to_string() << " + " << y.to_string() << " =" << endl;
    cout << ((x+y).to_string()) << endl << endl;
    cout << x.to_string() << " - " << y.to_string() << " =" << endl;
    cout << ((x-y).to_string()) << endl << endl;
    cout << x.to_string() << " * " << y.to_string() << " =" << endl;
    cout << ((x*y).to_string()) << endl << endl;
    cout << x.to_string() << " / " << y.to_string() << " =" << endl;
    cout << ((x/y).to_string()) << endl << endl;
    cout << "gcd(" << x.to_string() << "," << y.to_string() << ") =" << endl;
    cout << (gcd(x,y).to_string()) << endl << endl;
    cout << x.to_string() << " ^ " << yy << " =" << endl;
    cout << ((gefficient_exp(x,yy)).to_string()) << endl << endl;

    cout << y.to_string() << " + " << x.to_string() << " =" << endl;
    cout << ((y+x).to_string()) << endl << endl;
    cout << y.to_string() << " - " << x.to_string() << " =" << endl;
    cout << ((y-x).to_string()) << endl << endl;
    cout << y.to_string() << " * " << x.to_string() << " =" << endl;
    cout << ((y*x).to_string()) << endl << endl;
    cout << y.to_string() << " / " << x.to_string() << " =" << endl;
    cout << ((y/x).to_string()) << endl << endl;
    cout << "gcd(" << y.to_string() << "," << x.to_string() << ") =" << endl;
    cout << (gcd(y,x).to_string()) << endl << endl;
    cout << y.to_string() << " ^ " << xx << " =" << endl;
    cout << ((gefficient_exp(y,xx)).to_string()) << endl << endl;

    cout << "is_prime(" << x.to_string() << ") =" << endl;
    cout << ((x.is_prime())?"Yes":"No") << endl << endl;
    cout << "is_prime(" << y.to_string() << ") =" << endl;
    cout << ((y.is_prime())?"Yes":"No") << endl << endl;

    cout << w.to_string() << " + " << z.to_string() << " =" << endl;
    cout << ((w+z).to_string()) << endl << endl;
    cout << w.to_string() << " - " << z.to_string() << " =" << endl;
    cout << ((w-z).to_string()) << endl << endl;
    cout << w.to_string() << " * " << z.to_string() << " =" << endl;
    cout << ((w*z).to_string()) << endl << endl;
    cout << w.to_string() << " / " << z.to_string() << " =" << endl;
    cout << ((w/z).to_string()) << endl << endl;
    cout << "gcd(" << w.to_string() << "," << z.to_string() << ") =" << endl;
    cout << (gcd(w,z).to_string()) << endl << endl;
    cout << w.to_string() << " ^ " << xx << " =" << endl;
    cout << ((gefficient_exp(w,xx)).to_string()) << endl << endl;

    cout << z.to_string() << " + " << w.to_string() << " =" << endl;
    cout << ((z+w).to_string()) << endl << endl;
    cout << z.to_string() << " - " << w.to_string() << " =" << endl;
    cout << ((z-w).to_string()) << endl << endl;
    cout << z.to_string() << " * " << w.to_string() << " =" << endl;
    cout << ((z*w).to_string()) << endl << endl;
    cout << z.to_string() << " / " << w.to_string() << " =" << endl;
    cout << ((z/w).to_string()) << endl << endl;
    cout << "gcd(" << z.to_string() << "," << w.to_string() << ") =" << endl;
    cout << (gcd(z,w).to_string()) << endl << endl;
    cout << z.to_string() << " ^ " << xx << " =" << endl;
    cout << ((gefficient_exp(z,xx)).to_string()) << endl << endl;

    cout << "is_prime(" << w.to_string() << ") =" << endl;
    cout << ((w.is_prime())?"Yes":"No") << endl << endl;
    cout << "is_prime(" << z.to_string() << ") =" << endl;
    cout << ((z.is_prime())?"Yes":"No") << endl << endl;


    BigInteger xxx("10000000000000000"), yyy("100000000000");

    cout << xxx.to_string() << endl << yyy.to_string() << endl;

    cout << (gcd(xxx,yyy).to_string()) << endl << endl;

    cout << (BigInteger("-1") - BigInteger("1")).to_string() << endl;

    cout << (BigInteger("0") / BigInteger("1")).to_string() << endl;

    cout << (BigInteger("1") / BigInteger("0")).to_string() << endl;

    BigInteger ww("1583710171");

    cout << ww.is_prime() << endl;*/
    return 0;
}
