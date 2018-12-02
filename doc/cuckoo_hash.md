#### Cuckoo hasing[^1]
>**CUCKOO HASHING** is a dynamization of a static dictionary which uses two hash tables, $T_1$ and $T_2$, each consisting of $r$ words, and two hash functions $h_1, h_2: U \rightarrow \{ 0, \cdots, r - r \}$. Every key $x \in S$ is stored in cell $h_1(x)$ of $T_1$ or in cell $h_2(x)$ of $T_2$, but never in both.

##### Algorithms
1. *Lookup*
function lookup(x) 
    return $T_1[h_1(x)] = x \lor T_2[h_2(x)] = x$ 
end

2. *Insert*
The notation $x \leftrightarrow y$ means the swap operation between $x$ and $y$. The special value $\perp \in U$ is a sign assigned to every empty cells in hash tables.
function  procedure(x)
    if lookup(x) then return
    loop MaxLoop times
        $x \leftrightarrow T_1[h_1(x)]$
        if $x = \perp$ then return
        $x \leftrightarrow T_2[h_2(x)]$
        if $x = \perp$ then return
    end loop
    rehash()
    insert(x)
end


#### Reference
[^1]: Pagh R, Rodler F F. Cuckoo hashing[J]. Journal of Algorithms, 2004, 51(2): 122-144.
