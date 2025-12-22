let read file_name =
    let input = open_in file_name in

    let rec read_ranges () =
      let parse_range range_list =
        match range_list with
        |low::[high]->(int_of_string low,int_of_string high)
        |_->failwith "invalid input"
      in
      try
        let line = input_line input in
        match line with
        |""->[]
        |_-> (parse_range (String.split_on_char '-' line))::read_ranges()
      with
      |End_of_file -> []
    in
    let ranges = read_ranges () in
    let rec read_ingredients () =
      try
        let line = input_line input in
        (int_of_string line)::read_ingredients()
      with
      |End_of_file -> []
    in
    let ingredients = read_ingredients () in
    close_in input;
    (ranges,ingredients)

let main () =
  let ranges, ingredients = read "input.txt" in
  print_int (List.fold_left (
    fun acc ingredient ->
      if List.exists (
        fun range -> 
          let low,high = range in
          (low <= ingredient) && (high >= ingredient)
      ) ranges then
        acc + 1
    else 
      acc
  ) 0 ingredients);
  print_newline ()

let () = main ()