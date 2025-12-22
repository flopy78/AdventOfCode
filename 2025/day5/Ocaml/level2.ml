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
        |""->([],0)
        |_-> let lines,size = read_ranges () in
          (parse_range (String.split_on_char '-' line)::lines,size+1)
      with
      |End_of_file -> ([],0)
    in
    let ranges_list,size = read_ranges () in
    let ranges_array = Array.make size (0,0) in
    List.iteri (
      fun i range -> 
        ranges_array.(i) <- range
    ) ranges_list;
    close_in input;
    ranges_array

let main () =
  let compare_ranges r1 r2 = 
    if fst r1 = fst r2 then
      snd r1 - snd r2
    else
      fst r1 - fst r2
  in
  let ranges = read "input.txt" in
  Array.sort compare_ranges ranges;

  let answer = Array.fold_left ( 
      fun acc_tuple range ->
        (*print_int (snd acc_tuple);
        print_newline ();*)
        let i, acc = acc_tuple in
        let low,high = range in
          let cut_low,cut_high = 
          Array.fold_left (
            fun inner_acc range ->
              let low_acc, high_acc = inner_acc in
              let low_i, high_i = range in
              (max (high_i+1) low_acc, high_acc)
          ) (low, high) (Array.sub ranges 0 i) in
          if (cut_high - cut_low + 1 < 0) then
            (i+1,acc)
          else
            (i+1,acc+cut_high-cut_low+1)         
    ) (0,0) ranges in
    print_int (snd answer);
    print_newline ()
  

let () = main ()