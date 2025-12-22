let read file_name =
    let parse_range range_string =
        let liste = String.split_on_char '-' range_string in
        match liste with 
        |low::[high]->(int_of_string low,int_of_string high)
        |_->failwith "invalid input"
    in
    let input = open_in file_name in
    let line = input_line input in
    let ranges_string = String.split_on_char ',' line in
    List.map parse_range ranges_string



let main () = 
  let ranges = read "input.txt" in
  let counter = ref 0 in
  List.iter (
    fun (low,high) ->
      for n = low to high do
        let string_n = string_of_int n in
        let size = String.length string_n in
        if (size mod 2 = 0) && String.sub string_n 0 (size/2) = String.sub string_n (size/2) (size/2)  then
        counter := !counter + n
      done
  ) ranges;
  print_int !counter;
  print_newline ()
let () = main ()