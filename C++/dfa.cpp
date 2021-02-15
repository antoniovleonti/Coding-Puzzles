/*  Antonio Leonti
    2.14.2020
*/

#include <iostream>
#include <string>
#include <random>

using namespace std;

class Dfa
{

  private:
    size_t n_Q;     // number of states
    size_t n_F;     // number of accept states
    size_t q0;      // start state
    size_t** delta; // transition function
    string* sigma;  // alphabet
    size_t* F;      // accept states

    // utility for qsort and bsearch (for more quickly finding accept states)
    static int sizetcmp(const void *ap, const void *bp)
    {
        const size_t* a = (size_t*)ap;
        const size_t* b = (size_t*)bp;

        return (*a > *b) - (*a < *b);
    }

  public:
    // constuctor - create new dfa
    Dfa (size_t n_Q_, size_t n_F_, string sigma_,
        size_t** delta_, size_t q0_, size_t F_[n_F_])
    {
        n_Q = n_Q_;
        n_F = n_F_;
        q0 = q0_;
        sigma = new string(sigma_);

        // copy delta into dynamically allocated array
        delta = (size_t**)malloc(sizeof(size_t*) * n_Q);
        for (size_t i = 0; i < n_Q; i++)
        {
            delta[i] = (size_t*)malloc(sizeof(size_t) * sigma->length());
            for (size_t j = 0; j < sigma->length(); j++)
            {
                delta[i][j] = delta_[i][j];
            }
        }
        // copy array of accept states
        F = (size_t*)malloc(sizeof(size_t) * n_F);
        for (size_t i = 0; i < n_F; i++)
        {
            F[i] = F_[i];
        }
        qsort(F, n_F, sizeof(size_t), sizetcmp);
    }
    // deconstructor - free dynamically allocated resources
    ~Dfa (void)
    {
        for (size_t i = 0; i < n_Q; i++) free(delta[i]);
        free(delta);

        free(F);

        delete(sigma);
    }
    // accept or reject input string
    bool compute(string input)
    {
        size_t cur = q0;
        for (size_t i = 0; i < input.length(); i++)
        {
            size_t index = sigma->find(input[i]);
            if (index != string::npos)
            {
                cur = delta[cur][index];
            }
            else return false;
        }
        // search F for current state
        size_t* ptr = (size_t*)bsearch(&cur, F, n_F, sizeof(size_t), sizetcmp);
        return ptr != NULL;
    }
};

#define NF 1 // # of accept states
#define NQ 5 // # of states
#define NS 2 // # of elements (chars) in alphabet (sigma)

int main (int argc, char** argv)
{
    string sigma = "01"; //alphabet
    size_t q0 = 0; // start state
    size_t F[] = {4}; //final state(s)
    //                      q0    q1    q2    q3    q4
    size_t deltatmp[][NS] = {{1,0},{1,2},{3,0},{0,4},{4,4}};

    // dynamically allocated transition fn to be passed to constructor
    size_t** delta = (size_t**)malloc(sizeof(size_t*) * NQ);
    for (size_t i = 0; i < NQ; i++)
    {
        delta[i] = (size_t*)malloc(sizeof(size_t) * NS);
        for (size_t j = 0; j < NS; j++) delta[i][j] = deltatmp[i][j];
    }

    // construct dfa which accepts the following language:
    // { w | w = x0101y for some x and y }
    Dfa* dfa = new Dfa(NQ, NF, sigma, delta, q0, F);

    // finished with dynamically allocated array -- free it
    for (size_t i = 0; i < NQ; i++) free(delta[i]);
    free(delta);

    // if main is given input strings, compute those
    if (argc > 1)
    {
        bool out;
        for (size_t i = 1; i < argc; i++)
        {
            // test it out in the machine
            out = dfa->compute(argv[i]);
            // print results
            cout << "DFA("<< argv[i]<< ") = "<< (out ? "ACCEPT" : "REJECT")<< "\n";
        }
    }
    // otherwise generate random strings until one is accepted by dfa
    else
    {
        random_device* rand = new random_device();
        for (bool out = false; !out; )
        {
            // construct input string
            string input = "";
            for(size_t i = 0; i < 8; i++) input += sigma[(*rand)()%2];
            // test it out in the machine
            out = dfa->compute(input);
            // print results
            cout<<"DFA("<<input<< ") = "<<(out?"ACCEPT":"REJECT")<<"\n";
        }
    }

    delete(dfa);
    return 0;
}
