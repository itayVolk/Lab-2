unsorted: unique.c parity.c unsorted.c set.h
	gcc -o unique_unsorted unique.c unsorted.c
	gcc -o parity_unsorted parity.c unsorted.c
clean:; rm -rf unique parity
sorted: unique.c parity.c sorted.c set.h
	gcc -o unique_sorted unique.c sorted.c
	gcc -o parity_sorted parity.c sorted.c
