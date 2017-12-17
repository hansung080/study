package main

import (
	"fmt"
	"sync"
)

func Send(idx int) <-chan int {
	in := make(chan int)
	go func(idx int) {
		defer close(in)
		for i := 1; i <= 5; i++ {
			in <- idx * 100 + i
		}
	}(idx)

	return in
}

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

funcø main() {
	in1 := Send(1)
	in2 := Send(2)
	in3 := Send(3)
	out := FanIn(in1, in2, in3)

	for num := range out {
		fmt.Println(num)
	}
}

