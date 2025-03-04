#include <list>
#include <iostream>
#include <algorithm>
#include <cstdio>

void rec(std::list<int> &lst, int n, int k){
	if (lst.size() == k){
		for(int el: lst){
			printf("%d ", el); 
		}
		printf("\n");
	}




	for (int i = 1; i < n+1; i++){
		if (std::find(lst.begin(), lst.end(), i) == lst.end()){
			std::list<int> lst_cpy(lst);
			lst_cpy.push_back(i);
			rec(lst_cpy, n, k);
		}
	}



}



int main(){
    int n, k;

    std::list<int> lst;


    std::cin >> n;
    std::cin >> k;
    
    rec(lst, n, k);



}
