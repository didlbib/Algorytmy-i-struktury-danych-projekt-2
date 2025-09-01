# AISD2
#  Wyciągi i góry

## Opis problemu
Celem zadania jest znalezienie **najkrótszej trasy** przez dany teren opisany jako prostokątna siatka pól.  
Każde pole ma wysokość wyrażoną nieujemną liczbą całkowitą.  

Czas przejścia między polami zależy od różnicy wysokości:
- ⬆️ **Jeżeli A > B** (wchodzimy wyżej): czas = `A - B + 1` minut.  
- ⬇️ **Jeżeli A ≤ B** (schodzimy lub idziemy po równym): czas = `1` minuta.  

Możemy poruszać się tylko na pola sąsiadujące bokami (maksymalnie cztery kierunki).  
Nie możemy wychodzić poza mapę.  

Dodatkowo w obszarze mogą znajdować się **wyciągi**:
- Każdy wyciąg prowadzi z jednego pola do innego (jednokierunkowo).  
- Skorzystanie z wyciągu zajmuje określony czas.  
- Wyciąg kursuje co pewien ustalony interwał minutowy. Jeśli dotrzemy do pola startowego w czasie `t`, a najbliższy kurs przypada w czasie `k`, musimy czekać `(k - t)` minut, a następnie doliczamy czas przejazdu.  

Przykład:  
Jeżeli jesteśmy w polu startowym wyciągu w **8. minucie**, wyciąg kursuje co **5 minut**, a przejazd trwa **3 minuty**, to dotrzemy do pola docelowego w **13. minucie** (8 + 2 czekania + 3 jazdy).

---

## 📥 Wejście
Na wejściu podane są kolejno:
1. Szerokość i wysokość mapy.  
2. Pozycja startowa (kolumna, wiersz).  
3. Pozycja docelowa (kolumna, wiersz).  
4. Liczba wyciągów.  
5. Opisy wyciągów – dla każdego:  
   - pozycja startowa (kolumna, wiersz),  
   - pozycja docelowa (kolumna, wiersz),  
   - czas przejazdu w minutach,  
   - interwał odjazdu (kursuje co X minut).  
6. Wysokości wszystkich pól mapy.  

Wszystkie wartości są nieujemne.

---

## 📤 Wyjście
Należy wypisać **najkrótszy czas** potrzebny, aby dotrzeć z punktu startowego do punktu docelowego.

---

## 🔍 Przykład 1
**Wejście**

9 8 0 0 8 7 0
0 0 0 0 0 0 0 0 8 
0 9 9 9 9 9 9 9 0 
0 1 0 1 0 0 0 9 0 
0 9 0 0 0 1 0 9 0 
0 9 1 1 1 1 0 9 0 
0 9 0 0 0 0 0 9 0 
0 9 9 9 9 1 9 9 0 
8 0 0 0 0 0 0 0 0 

**Wyjście**

18

