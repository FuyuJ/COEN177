o "----------FIFO----------"
cat testInput.txt | ./fifo 10 
echo "----------End FIFO----------"
echo
echo "----------LRU----------"
cat testInput.txt | ./lru 10 
echo "----------End LRU----------"
echo
echo "----------Second Chance----------"
cat testInput.txt | ./sec_chance 10 
echo "----------End Second Chance----------"
echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./fifo 10 | wc -l
cat accesses.txt | ./fifo 50 | wc -l
cat accesses.txt | ./fifo 100 | wc -l
cat accesses.txt | ./fifo 250 | wc -l
cat accesses.txt | ./fifo 500 | wc -l
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./lru 10 | wc -l
cat accesses.txt | ./lru 50 | wc -l
cat accesses.txt | ./lru 100 | wc -l
cat accesses.txt | ./lru 250 | wc -l
cat accesses.txt | ./lru 500 | wc -l
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accesses.txt | ./sec_chance 10 | wc -l
cat accesses.txt | ./sec_chance 50 | wc -l
cat accesses.txt | ./sec_chance 100 | wc -l
cat accesses.txt | ./sec_chance 250 | wc -l
cat accesses.txt | ./sec_chance 500 | wc -l
echo
make clean;
echo
