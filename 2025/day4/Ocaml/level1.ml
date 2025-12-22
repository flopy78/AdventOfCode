let read file_name =
  let input = open_in file_name in
  let rec read_lines () =
    try
      let line = input_line input in
        let lines,size = read_lines () in
        (line::lines,size+1)
    with
    |End_of_file -> ([],0)
  in 
  let liste,size = read_lines () in
  let array = Array.make size "" in
  List.iteri (
    fun i line ->
      array.(i) <- line
  ) liste;
  close_in input;
  array

let main () =
  let is_valid row column array =
    row >= 0 && column >= 0 && row < Array.length array && column < String.length array.(row)
  in
  let array = read "input.txt" in
  let accessible_rollpapers = ref 0 in
  Array.iteri (
    fun row string ->
      String.iteri (
        fun column char ->
          if char = '@' then begin
            let voisins = ref 0 in

            for dr = -1 to 1 do
              for dc = -1 to 1 do
                if (dr,dc) <> (0,0) && is_valid (row+dr) (column+dc) array && array.(row+dr).[column+dc] = '@' then
                  incr voisins
              done
            done;
            if !voisins < 4 then
              incr accessible_rollpapers
          end
      ) string
  ) array;
  print_int !accessible_rollpapers;
  print_newline ()

let () = main ()