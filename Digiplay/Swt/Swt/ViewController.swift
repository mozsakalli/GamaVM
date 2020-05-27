//
//  ViewController.swift
//  Swt
//
//  Created by mustafa on 15.05.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        let arr = [12, 120]
        
        do {
            try print(arr[12])
            
        } catch {
            print("ERRROR");
        }
    }


}

