insertionsort: quicksort freetext
	g++ insertionsort_AndreaLi.cpp -o insertionsort

quicksort:
	g++ quicksort_AndreaLi.cpp -o quicksort

freetext:
	$(MAKE) -C freetext_search freetext