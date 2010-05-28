let m = Array.init 9 (fun _ -> input_line stdin)

let print() = Array.iter print_endline m

let rec invalid ?(i=0) x y n =
  i<9 && (m.(y).[i] = n || m.(i).[x] = n ||
      m.(y/3*3 + i/3).[x/3*3 + i mod 3] = n || invalid ~i:(i+1) x y n)

let rec fold f accu l u = if l=u then accu else fold f (f accu l) (l+1) u
  
let rec search ?(x=0) ?(y=0) f accu = match x, y with
    9, y -> search ~x:0 ~y:(y+1) f accu (* Next row *)
  | 0, 9 -> f accu                      (* Found a solution *)
  | x, y ->
      if m.(y).[x] <> '0' then search ~x:(x+1) ~y f accu else
        fold (fun accu n ->
                let n = Char.chr (n + 48) in
                if invalid x y n then accu else
                  (m.(y).[x] <- n;
                   let accu = search ~x:(x+1) ~y f accu in
                   m.(y).[x] <- '0';
                   accu)) accu 1 10


let () = Printf.printf "%d solutions\n" (search (fun i -> print(); i+1) 0)
