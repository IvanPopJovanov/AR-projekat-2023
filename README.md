# AR-projekat-2023

Projekat za kurs Automatsko Rezonovanje na master studijama Matematičkog fakulteta, Univerzitet u Beogradu. 

Ivan Pop-Jovanov, 1066/2022

U ovom projektu je implementirana Knuth-Bendix procedura upotpunjavanja iz rada: 

> Knuth, Donald E., and Peter B. Bendix. "Simple word problems in universal algebras." Automation of Reasoning: 2: Classical Papers on Computational Logic 1967–1970 (1983): 342-376.

## Prevođenje

Pozicionirati se u folder projekta i pokrenuti `make`. Treba da se pojavi fajl `./main`. 

## Pokretanje 

Unutar projekta su data dva test ulazna fajla: `test1.txt` i `test2.txt`. Pokrenuti ih sa `cat test1.txt | ./main`. 

Sintaksa ulaza u program je sledeća: Prvo ide redosled težina funkcijskih simbola unutar specijalnog predikata `ord`. Nakon toga se nabrajaju ulazne jednakosti sa tačkazarezima na kraju svake jednakosti. Unutar jednakosti funkcijski simboli se pišu početnim malim slovom, a promenjive početnim velikim slovom. 

Primer ulaza: 
```
ord(one,times,i);
times(one,X) = X;
times(i(X),X) = one;
times(times(X,Y),Z) = times(X, times(Y,Z));
```
