package main

import (
	"fmt"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			fmt.Printf("%dth goroutine.\n", i+1)
		}(i)
	}

	wg.Wait()
	fmt.Println("main routine.")
}
