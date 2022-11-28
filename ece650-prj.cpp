//Importing all the main libraries
#include <bits/stdc++.h> //Header file that include all the major standar libraries, thus increasing compile time for the code
#include <sstream> //used for insertion and extraction of data from stringStream. 
#include <fstream>
#include <string> //for importing the string in the file
#include "minisat/core/SolverTypes.h" //Including the minisat solver for the code 
#include "minisat/core/Solver.h" //Including the minisat solver for the code
using namespace std; //for the major function we need to use std:: but importing the namespace std reduce time while writing 
#include <pthread.h>
#include <time.h>
#include <signal.h>

vector<int> ijdetMatrixOriginal;
int vertices;

vector<int> output_2;
vector<int> output_1;
vector<int> output_3;


int flag =0 ;


//Function to parse the input from the string and check if the input is in the correct format or it is not in the correct format, and the vertices are less than the maximum vertices allowed
string parse_inputString(int vertices, string s)
{
    string delimiter_one = "}";//we get the } to show the end of the list of edges
    string delimiter_two = "<"; // to state the start of the list of edges
    string delimiter_three = ">"; // to state the end of the list of edges
    string comma = ","; // to seprate the list of edges
    size_t position = 0; //specifying the two positions , one and two one is for the start and two is for the end
    size_t position2 = 0; //specifying the two positions , one and two
    string token;
    int vint;

    if (s.find("E") == 0) {// if in the string we find the "E" then 
        s.erase(0,3);//removing the firs the character that are "E {"
        position2 = s.find(delimiter_one);//finding the postion where the string ends and erasing it in the next line
        s.erase(position2,1);//earsing the last two characters hence we remain with the only list of edges
    }
    string scheck = s;//copying the string s to scheck
    while ((position = s.find(delimiter_two)) != string::npos) {
                s.erase(position,1);
                position2 = s.find(delimiter_three);
                s.erase(position2,1);
            }
//while loop to find the strings
    while ((position = s.find(comma)) != string::npos) { //npos is the end of the string position 
                token = s.substr(0,position); //getting the vertices from the list of edges
                vint = atoi(token.c_str()); //convert string to integer
                if(vint >= vertices)//if the vertices is more than the maximum vertices allowed return error or empty string in this case and display error
                    {
                    scheck = " ";//empty string is returned
                    return scheck;//returning empty string
                    }
                else
                    {
                    s.erase(0,token.length()+1);//erasing the vertices we found in the string and checking the other vertices
                    }
                }
        vint = atoi(s.c_str());//this will check if the input is not in the correcto order, in that case it will generate error for the code and return empty string
        if(vint >= vertices)
                        {
                        scheck = " ";//empty string is returned
                        return scheck;//returning empty string
                        }


    return scheck;

}


void approx_vc_2(int Vertices1,vector<int> ijdetMatrix){
    //string solution="";
    while(true){
        int u,v;
        for (int i=0; i < ijdetMatrix.size()-1; i++){

            if (ijdetMatrix.at(i) !=0 ){
                u = ijdetMatrix.at(i);
                if(i%2==0){
                    v= ijdetMatrix.at(i+1);
                }
                else{
                    v= ijdetMatrix.at(i-1);
                }
                
            }
        }

        for (int i=0; i < ijdetMatrix.size(); i++){
            if (ijdetMatrix.at(i)==u){
                ijdetMatrix.at(i)=0;
                if(i%2==0){
                    ijdetMatrix.at(i+1)=0;
                }
                else{
                    ijdetMatrix.at(i-1)=0;
                }
            }
        }
        for (int i=0; i < ijdetMatrix.size(); i++){
            if (ijdetMatrix.at(i)==v){
                ijdetMatrix.at(i)=0;
                if(i%2==0){
                    ijdetMatrix.at(i+1)=0;
                }
                else{
                    ijdetMatrix.at(i-1)=0;
                }
            }
        }
        output_2.push_back(u);
        output_2.push_back(v);
        //solution=solution+to_string(u)+","+to_string(v)+",";
        bool flag = true;
        for (int i=0; i < ijdetMatrix.size(); i++){

            if( ijdetMatrix.at(i) != 0){
                flag = false;
                break;
            }
        }

        if(flag == true){
            break;
        }   
    }
}

void* threadApprox_vc_2(void* arg){

    
    clock_t start, end;

    double duration;

    start = clock();

    approx_vc_2(vertices,ijdetMatrixOriginal);

    end = clock();

    duration = (double)(end-start)/ CLOCKS_PER_SEC;

    //cout<<"Duration,ApproxVC2,"<<duration*1000<<'\n';

    return NULL;
    
}


void approx_vc_1(int Vertices1,vector<int> ijdetMatrix){
    
    //string solution="";

    while(true){
        ///int arr[Vertices1-1]={0};
        vector<int> arr={};

        for (int i=0; i < Vertices1+1; i++){
            arr.push_back(0);
        }

        for (int i=0; i < ijdetMatrix.size(); i++){
        arr[ijdetMatrix.at(i)]=arr[ijdetMatrix.at(i)]+1;
        
        }

        int g =0;
        int index=-1;
        for(int i =1; i < Vertices1+1; i++ ){
            if (arr[i]> g){
                index =i;
                g=arr[i];
            }
        }
        //index = index +1;
        for (int i=0; i < ijdetMatrix.size(); i++){

            if (ijdetMatrix.at(i)==index){
                ijdetMatrix.at(i)=0;
                if(i%2==0){
                    ijdetMatrix.at(i+1)=0;
                }
                else{
                    ijdetMatrix.at(i-1)=0;
                }
            }
        }

        output_1.push_back(index);
        //solution=solution+to_string(index)+",";
        arr[index]=0;
        bool flag = true;
        for (int i=0; i < ijdetMatrix.size(); i++){

            if( ijdetMatrix.at(i) != 0){
                flag = false;
                break;
            }
        }

        if(flag == true){
            break;
        }


    }
}

void* threadApprox_vc_1(void* arg){
    clock_t start, end;

    double duration;

    start = clock();

    approx_vc_1(vertices,ijdetMatrixOriginal);

    end = clock();

    duration = (double)(end-start)/ CLOCKS_PER_SEC;

    //cout<<"Duration,ApproxVC1,"<<duration*1000<<'\n';

    return NULL;
    
}
    


//Function call to find the vertex cover
void vertex_coversat(int Vertices1,vector<int> ijdetMatrix)//input parameters being the maximum number of vertices and the list of edges with source and destination
{

 std::vector<int> final_answer;//creating the final_answer vector

 int k,minimum,maximum;
 minimum = 0;//minimum vertex number
 maximum = Vertices1;//maximum vertex number
 int n = Vertices1;//creating the copy fo the vertices
 while(minimum<=maximum)
 {
    k = int (minimum + maximum )/ 2;//finding the mid
     std::vector<std::vector<Minisat::Lit> > x(n);//using the sat sovler

        Minisat::Solver solver;//loop to provide the input as the clauses and the using the binary
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < k; j++)
            {
                Minisat::Lit li = Minisat::mkLit(solver.newVar());
                x[i].push_back(li);
            }
        }

     //At least one of the vertice is the ith vertex in the vertex cover from teh ajancy matrix
        for(int i = 0; i < k; i++)
        {
            Minisat::vec<Minisat::Lit> temp;
            for(int j = 0; j < n; j++)
            {
                temp.push(x[j][i]);
            }
             solver.addClause( temp );//adding clause to the sat sovler
             temp.clear();
        }

       // No one vertex can  appear twice in vertex cover problem as given
        for(int i=0;i< n;i++)
        {
            for(int j=0;j<k-1;j++)
            {
                for (int ab=j+1;ab<k;ab++)
                {
                    solver.addClause(~x[i][j],~x[i][ab]);//adding a clause to the sat sovler
                }

            }
        }
 
        //No more than one vertex in two position in the vortex cover as provided 
        for(int i=0;i< k;i++)
        {
            for(int j=0;j<n-1;j++)
            {
                for (int ab=j+1;ab<n;ab++)
                {
                    solver.addClause(~x[j][i],~x[ab][i]);//adding the clause to the vertex cover
                }

            }
        }
        //Every edge is incident on at least one vertex in vertex cover
        int len_size = ijdetMatrix.size();
            for(int j=0;j<len_size;j+=2)
            {       int q = ijdetMatrix[j];
                    int rs = ijdetMatrix[j+1];
                    
                Minisat::vec<Minisat::Lit> temp1;
                 for(int i=0;i< k;i++)
                 {
                   temp1.push(x[q][i]);
                   temp1.push(x[rs][i]);
                    
                 }
                 solver.addClause(temp1);
                 temp1.clear();
            }

          // Checking for the solution fromt the ajacency matrix
    if (flag == 1){
        cout<<"Timeout"<<endl;
        
    }      
    auto sat = solver.solve();
     if (sat) {
                        maximum = k-1;
                       final_answer.clear();
                       for(int i = 0; i < n; i++)
                        {
                            for(int j = 0; j < k; j++)
                            {
                              Minisat::lbool tf=solver.modelValue(x[i][j]);
                                if(tf==Minisat::l_True)
                            {   

                                final_answer.push_back(i);
                            }

                
     }}}
     else
     {
                    minimum = k+1;
        }


 }

            int xl = final_answer.size();
            output_3= final_answer;
            final_answer.clear();
            

            
}
//The driver program

void* threadVertex_coversat(void* arg){
    clock_t start, end;

    double duration;

    start = clock();

    vertex_coversat(vertices,ijdetMatrixOriginal);

    end = clock();

    duration = (double)(end-start)/ CLOCKS_PER_SEC;

    //cout<<"Duration,Coversat,"<<duration*1000<<'\n';
    return NULL;
    
}


void printOutput(){

    

    cout << "CNF-SAT-VC: ";
    sort(output_3.begin(), output_3.end());
    for(int i =0; i < output_3.size(); i++){
        if(i < output_3.size()-1){
        cout<<output_3[i]<<',';
        }
        else{
            cout<<output_3[i];
        }
    }
    cout << "\n";

	cout << "APPROX-VC-1: ";
    sort(output_1.begin(), output_1.end());
    for(int i =0; i < output_1.size(); i++){
        if(i < output_1.size()-1){
        cout<<output_1[i]<<',';
        }
        else{
            cout<<output_1[i];
        }
    }
    cout << "\n";
    cout << "APPROX-VC-2: ";

    sort(output_2.begin(), output_2.end());
    for(int i =0; i < output_2.size(); i++){
        if(i < output_2.size()-1){
        cout<<output_2[i]<<',';
        }
        else{
            cout<<output_2[i];
        }
    }
    cout << "\n";
    output_2.clear();
    output_1.clear();
    flag =0;

    std::cout<<std::endl;
    
}



void* threadIO(void* arg){

    using Minisat::mkLit;//importing the mklit library 
    using Minisat::lbool;//importing the lbool from the minisat solver
    string v;//string of number of vertices being created
    string s;//string for the edges 
    string scheck;//we will use the scheck for keeping the backup of the string created above and have 
    //Parsing Operator Variables for the proper functioning of the program
    string vdelimiter = "V ";// for finding the V in the input string 
    size_t vposition = 0;//position of the vertices
    string spath;//variable to find the shortest path
    string delimiter_two = "<"; // to state the start of the list of edges
    string delimiter_three = ">"; // to state the end of the list of edges
    string comma = ","; // to seprate the list of edges
    size_t position = 0; //specifying the two positions , one and two, one is for the start and two is for the end
    size_t position2 = 0; //specifying the two positoins, one and two , one is for the start and two is for the end
    size_t spos = 0;
    string token;
    int sr,des;

    vector<int> path; //Variable for the shortest path array
    
    int x;  //Integer Values
    // Preparing the adjancy matrix


    while(std::getline(cin,v))//while loop till the end of line
    {
        //EOF
        if(v == "") continue;//if the nubmer of vertices is not provided we move one

        //Pick Vertice Number
        if (v.find("V ") == 0)//finding the V in the first string
        {
                    v.erase(vposition,2);//erasing the first two characters, we get the vertices
		    x=atoi(v.c_str());//converting the string vertices to the integer value
                    vertices = x+1;//adding one as we start from zero
                    path.clear();//variable for the shortest path array
                    scheck.clear();//clearing the scheck string as well

        }
            //Edge Input
        if (v.find("E ") == 0)//if the we find E in the string then specific set of conditions need to be follwed
        {
            
            s = v;//creating the backup fo the string 
            scheck = parse_inputString(vertices,s);//checking whether the list of edges provided is correct
            if (scheck!= " ")//if the empty string is not returned we go through the instructions
            {
                while ((position = scheck.find(delimiter_two)) != string::npos)//program to create the adjacncy matrix  //starting from < 

                {
                        position2 = scheck.find(delimiter_three);//means finding the first edge// ending >
                        token = scheck.substr(position+1, position2-1);// so we find the 'verticex, vertiex'
                        spos = token.find(comma);//finding the comma in the string shortened
                        sr = atoi(token.substr(0,spos).c_str());//getting the two vertices, this one being the start
                        //cout << sr;
                        ijdetMatrixOriginal.push_back(sr);//adding to the vector
                        token.erase(0,spos+1);//erasing the start vertices
                        des = atoi(token.c_str());//getting the destination vertices
                        //cout << des;
                        ijdetMatrixOriginal.push_back(des);//adding the destination to the vertices
                        scheck.erase(position, position2+2);// getting the string scheck and erasing teh edge and moving ahead
                    }
                    int s;

                    pthread_t thread0, thread1, thread2;
                    s = pthread_create(&thread0, NULL, threadApprox_vc_2, NULL);
                    s = pthread_create(&thread1, NULL, threadApprox_vc_1, NULL);
                    s = pthread_create(&thread2, NULL, threadVertex_coversat, NULL);
                    
                    pthread_join(thread0, NULL);
                    pthread_join(thread1, NULL);
                    pthread_join(thread2, NULL);
                    printOutput();
                    
                    ijdetMatrixOriginal.clear();

            }
            else cerr << "Error: Invalid Entry, Please try again"<< endl;//else we will print out the error if , the list returned is empty

        }


    }
    return NULL;
}




int main(int argc, char** argv) {

	int s;
	pthread_t threadio;
	s = pthread_create(&threadio, NULL, threadIO, NULL);
	pthread_join(threadio, NULL);
	return 0;
}