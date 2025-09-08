fn selection_sort_less_complicated(unsorted: &mut [i32]) {
    println!("Less complicated Sort: ");
    for i in 0..unsorted.len() {
        for j in (i + 1)..unsorted.len() {
            if unsorted[i] > unsorted[j] {
                let temp = unsorted[i];
                unsorted[i] = unsorted[j];
                unsorted[j] = temp;
            }
        }
    }
}

fn selection_sort(unsorted: &mut [i32]) {
    println!("Little Complicated Sort: ");
    for i in 0..unsorted.len() {
        let mut min = i;
        for j in (i + 1)..unsorted.len() {
            if unsorted[min] > unsorted[j] {
                min = j;
            }
        }

        if min != i {
            let temp = unsorted[i];
            unsorted[i] = unsorted[min];
            unsorted[min] = temp;
        }
    }
}

fn main() {
    let mut unsorted = [11, 23, 8, 9, 1, 3, 5, 2];

    println!("Before sorting: ");
    for i in 0..unsorted.len() {
        print!("{}, ", unsorted[i]);
    }
    println!("\n");

    selection_sort_less_complicated(&mut unsorted);
    // selection_sort(&mut unsorted);
    
    println!("After sorting: ");
    for i in 0..unsorted.len() {
        print!("{}, ", unsorted[i]);
    }
    println!("");
}
