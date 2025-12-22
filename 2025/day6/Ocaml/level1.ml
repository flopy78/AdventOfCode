let read file_name =
  let input = open_in file_name in
  let rec read_lines () =
    try
      let line = input_line input in
      let lines,size = read_lines () in
      ((List.filter (fun str -> str <> "") (String.split_on_char ' ' line))::lines,size+1)
    with
    |End_of_file -> ([],0)
  in
  let reversed_lines_list, size = read_lines () in
  let op_list,parsed_lines_list =
    match List.rev reversed_lines_list with
    |op::tail -> 
      op,(List.map (fun liste -> List.map int_of_string liste) tail)
    |_->failwith "invalid input reading"
  in
  let parsed_lines_array = Array.make (size-1) [] in
  List.iteri (
    fun i line-> parsed_lines_array.(i) <- line
  ) parsed_lines_list;
  close_in input;
  (op_list, parsed_lines_array)




  
let rec compute op_list lines acc =
  match op_list with
  |[] -> acc 
  |op::tail_op ->
    compute tail_op (Array.init (Array.length lines) (
      fun i ->
        match lines.(i) with
        |[]->failwith "invalid input"
        |h::t->t
    ))
    (acc + Array.fold_left (
      fun local_acc line ->
        match line with
        |[]->failwith "invalid input"
        |h::t->
          if op = "+" then
            local_acc + h
          else
            local_acc * h
    ) (if op = "+" then 0 else 1) lines)

let main () =
  let op_list, lines = read "input.txt" in

  let answer = compute op_list lines 0 in
  print_int answer;
  print_newline ()

let () = main ()