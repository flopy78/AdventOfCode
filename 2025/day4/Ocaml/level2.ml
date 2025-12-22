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
  let array = Array.make size [||] in
  List.iteri (
    fun i line ->
      array.(i) <- (Array.init (String.length line) (fun j -> line.[j]))
  ) liste;
  close_in input;
  array

let seek_accessible_rollpapers array =
  let is_valid row column array =
    row >= 0 && column >= 0 && row < Array.length array && column < Array.length array.(row)
  in
  let accessible_rollpapers = ref [] in
  let n_accessible_rollpapers = ref 0 in
  Array.iteri (
    fun row string ->
      Array.iteri (
        fun column char ->
          if char = '@' then begin
            let voisins = ref 0 in

            for dr = -1 to 1 do
              for dc = -1 to 1 do
                if (dr,dc) <> (0,0) && is_valid (row+dr) (column+dc) array && array.(row+dr).(column+dc) = '@' then
                  incr voisins
              done
            done;
            if !voisins < 4 then begin
              accessible_rollpapers := (row,column)::!accessible_rollpapers;
              incr n_accessible_rollpapers
            end
          end
      ) string
  ) array;
  (!accessible_rollpapers,!n_accessible_rollpapers)

let rec remove_rollpapers array n_already_removed =
  let rollpapers_to_remove,length = seek_accessible_rollpapers array in
  match rollpapers_to_remove with
  |[]->n_already_removed
  |_-> List.iter (
    fun rollpaper -> 
      let row,col = rollpaper in
      array.(row).(col) <- ' '
  ) rollpapers_to_remove;
  remove_rollpapers array (n_already_removed + length)

let main () =

  let array = read "input.txt" in
  print_int (remove_rollpapers array 0);
  print_newline ()

let () = main ()