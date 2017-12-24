package main

import (
	"fmt"

	"golang.org/x/net/context"
)

func Range(ctx context.Context, start, step int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for num := start; ; num += step {
			select {
			case out <- num:
			case <-ctx.Done():
				return
			}
		}
	}()

	return out
}

type IntPipe func(context.Context, <-chan int) <-chan int

func FilterMultiple(n int) IntPipe {
	return func(ctx context.Context, in <-chan int) <-chan int {
		out := make(chan int)
		go func() {
			defer close(out)
			for x := range in {
				if x % n == 0 {
					continue
				}

				select {
				case out <- x:
				case <-ctx.Done():
					return
				}
			}
		}()

		return out
	}
}

func Primes(ctx context.Context) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		c := Range(ctx, 2, 1)
		for {
			select {
			case num := <-c:
				c = FilterMultiple(num)(ctx, c)
				select {
				case out <- num:
				case <-ctx.Done():
					return
				}
			case <-ctx.Done():
				return
			}
		}
	}()

	return out
}

func PrintPrimes(max int) {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	for prime := range Primes(ctx) {
		if prime > max {
			break
		}

		fmt.Print(prime, ", ")
	}

	fmt.Println()
}

func main() {
	PrintPrimes(30)
}
