package main

import (
	"fmt"
	"time"
	"sync"
)

func main() {
	c := make(chan int)

	var wg sync.WaitGroup
	for i := 0; i < 3; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			defer func() { fmt.Printf("%dth goroutine ended.\n", i+1) }()
			for num := range c {
				time.Sleep(time.Second)
				fmt.Printf("%dth goroutine: %d\n", i+1, num)
			}
		}(i)
	}

	for i := 0; i < 10; i++ {
		c <- i
	}

	close(c)
	fmt.Println("closed channel.")
	wg.Wait()
}
