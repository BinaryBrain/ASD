/* 
 * File:   IndexMinPQ.h
 * Author: paulnta
 *
 * Created on 3. janvier 2015, 06:20
 */

#ifndef INDEXMINPQ_H
#define	INDEXMINPQ_H


class IndexMinPQ {
    int N, size, *heap, *index, *keys;

    void exch(int i, int j) {
        int t = heap[i]; heap[i] = heap[j]; heap[j] = t;
        index[heap[i]] = i; index[heap[j]] = j;
    }
    
    bool less(int a, int b){
        return keys[heap[a]] > keys[heap[b]];
    }
    
    void swim(int k)    {
        while(k > 1 && less(k/2,k)) {
            exch(k, k/2);
            k = k/2;
        }
    }
    void sink(int k)  {
        
        while(2*k <= size) 
        {
            int j = 2*k;
            if(j < size && less(j,j+1))
                j++;
            if(!less(k,j))
                break;
            exch(k, j);
            k = j;
        }
    }
public:
    // Création d'une IndexMinPQ vide qui peut contenur au max N éléments
    IndexMinPQ(int N)  {
        this->N = N;
        size = 0;
        keys = new int[N + 1];
        heap = new int[N + 1];
        index = new int[N + 1];
        for(int i = 0; i <= N; i++)
            index[i] = -1;
    }
    ~IndexMinPQ() {
        delete [] keys;
        delete [] heap;
        delete [] index;
    }
    // Vérifier si la queue de priorité est vide
    bool isEmpty()  {
        return size == 0;
    }
    // Vérifie la présence d'un index dans la pq
    bool contains(int i)    {
        return index[i] != -1;
    }
    
    //Associe une clé a un index
    void insert(int i, int key) {
        size++;
        index[i] = size;
        heap[size] = i;
        keys[i] = key;
        swim(size);
    }
    // supprime la clé minimum et return son index
    int deleteMin() {
        int min = heap[1];
        exch(1, size--);
        sink(1);
        index[min] = -1;
        heap[size+1] = -1;
        return min;
    }
    // Décrémente une clé à l'index i à la valeur key
    void decreaseKey(int i, int key)    {
        keys[i] = key;
        swim(index[i]);
    }
};



#endif	/* INDEXMINPQ_H */

