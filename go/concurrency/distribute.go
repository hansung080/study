package main

import (
	"fmt"
	"sync"
	"time"
)

func PlusOne(in <-chan int) <-chan int { // a kind of IntPipe
	out := make(chan int)
	go func() {
		defer close(out)
		for num := range in {
			out <- num + 1
		}
	}()

	return out
} 

type IntPipe func(<-chan int) <-chan int

func Chain(pipes ...IntPipe) IntPipe {
	return func(in <-chan int) <-chan int {
		c := in
		for _, pipe := range pipes {
			c = pipe(c)
		}

		return c
	}
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

func Distribute(pipe IntPipe, n int) IntPipe {
	return func(in <-chan int) <-chan int {
		outs := make([]<-chan int, n)
		for i := 0; i < n; i++ {
			outs[i] = pipe(in)
		}

		return FanIn(outs...)
	}
}

func main() {
	start := time.Now()
	in := func() <-chan int {
		in := make(chan int)
		go func() {
			defer close(in)
			for i := 1; i <= 10000000; i++ {
				in <- i
			}
		}()

		return in
	}()

	//PlusTwo := Chain(PlusOne, PlusOne) // elapsed: 25.568617392s
	PlusTwo := Distribute(Chain(PlusOne, PlusOne), 10) // elapsed: 21.820707922s
	for num := range PlusTwo(in) {
		fmt.Println(num)
	}

	elapsed := time.Now().Sub(start)
	//elapsed := time.Since(start)

	fmt.Println("elapsed:", elapsed)
}
