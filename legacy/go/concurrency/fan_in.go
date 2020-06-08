package main

import (
	"fmt"
	"sync"
)

func FanIn(ins ...<-chan int) <-chan int {
	out := make(chan int)
	var wg sync.WaitGroup
	for _, in := range ins {
		wg.Add(1)
		go func(in <-chan int) {
			defer wg.Done()
			for num := range in {
				out <- num
			}
		}(in)
	}

	go func() {
		wg.Wait()
		close(out)
	}()

	return out
}

func main() {
	in1, in2, in3 := make(chan int), make(chan int), make(chan int)
	send := func(c chan<- int, begin, end int) {
		defer close(c)
		for i := begin; i < end; i++ {
			c <- i
		}
	}

	go send(in1, 100, 105)
	go send(in2, 200, 205)
	go send(in3, 300, 305)

	for num := range FanIn(in1, in2, in3) {
		fmt.Println(num)
	}
}
