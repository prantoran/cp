package main

import (
	"bufio"
	"fmt"
	"log"
	"math/rand"
	"os"
	"sync"
	"time"
)

type edge struct {
	u, v int
	p    float32
}

func (e *edge) String() string {
	return fmt.Sprintf("%d %d %.1f\n", e.u, e.v, e.p)
}

type testcase struct {
	n, e  int
	edges []edge
}

func (t *testcase) String() string {
	ret := ""
	ret += fmt.Sprintf("%d %d\n", t.n, t.e)

	for i := 0; i < t.e; i++ {
		ret += t.edges[i].String()
	}

	return ret
}

func generate(i int, wg *sync.WaitGroup) {
	defer wg.Done()
	s1 := rand.NewSource(int64(i) + time.Now().UnixNano())
	r1 := rand.New(s1)
	t := r1.Intn(10) + 1
	cases := make([]testcase, t)

	for ca := 0; ca < t; ca++ {
		n := r1.Intn(49) + 2
		if ca < 7 {
			n = r1.Intn(9) + 2
		}
		e := n - 1
		if n > 2 {
			e += r1.Intn(((n * (n - 1)) / 2) - n + 2)

		}
		edges := make([]edge, e)

		edgesCnt := 0

		perm := make([]int, n)

		marked := make(map[int]int)

		mask := make(map[int]int)

		for i := 0; i < n; i++ {
			mask[i] = int(1 << uint(i))
		}

		for j := 0; j < n; j++ {
			perm[j] = j + 1
		}

		for j := 0; j < n; j++ {
			id := r1.Intn(n-j) + j
			u := perm[id]

			perm[j], perm[id] = perm[id], perm[j]

			marked[j] = u

			if j == 0 {
				continue
			}

			id2 := r1.Intn(j)
			v := marked[id2]

			p := float32(r1.Intn(10)+1) / 10

			mask[u] |= (v - 1)
			mask[v] |= (u - 1)

			edges[edgesCnt] = edge{
				u: u,
				v: v,
				p: p,
			}

			edgesCnt++
		}

		extraEdges := e - n + 1

		fullmask := int(1<<uint(n)) - 1

		for j := 0; j < extraEdges; j++ {
			u := r1.Intn(n)
			for mask[u] == fullmask {
				u = (u + 1) % n
			}
			u++
			umask := mask[u]

			v := r1.Intn(n)

			for umask&(1<<uint(v)) > 0 {
				v = (v + 1) % n
			}
			v++

			p := float32(r1.Intn(10)+1) / 10

			mask[u] |= (v - 1)
			mask[v] |= (u - 1)

			edges[edgesCnt] = edge{
				u: u,
				v: v,
				p: p,
			}

			edgesCnt++
		}

		cases[ca] = testcase{
			n:     n,
			e:     e,
			edges: edges,
		}

	}

	filePath := fmt.Sprintf("data/input%02d.txt", i)
	fmt.Println("filePath:", filePath)

	ret := fmt.Sprintf("%d\n", t)
	for ca := 0; ca < t; ca++ {
		ret += cases[ca].String()
	}

	f, err := os.Create(filePath)
	if err != nil {
		log.Println(err)
		return
	}

	defer f.Close()

	w := bufio.NewWriter(f)
	_, err = w.WriteString(ret)
	if err != nil {
		log.Println(err)
		return
	}

	w.Flush()
}

func main() {
	wg := sync.WaitGroup{}
	for i := 2; i <= 10; i++ {
		wg.Add(1)
		go generate(i, &wg)
	}

	wg.Wait()
}
