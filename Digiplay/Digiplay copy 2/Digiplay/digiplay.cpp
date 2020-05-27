//
//  digiplay.c
//  Digiplay
//
//  Created by mustafa on 20.04.2020.
//  Copyright © 2020 mustafa. All rights reserved.
//

#include "digiplay.h"

namespace digiplay {

int Sprite2D::GlobalFrameVersion = 0;
int Sprite2D::InvalidationCounter = 0;

Bag<Sprite2D*> Sprite2D::IterateBag;
void Sprite2D::IterateChildren(Sprite2D* root, Action action) {
    if(!root) return;
    IterateBag.Reset();
    IterateBag.Add(root);
    int index = 0;
    while (index < IterateBag.Count) {
        Sprite2D* item = IterateBag.Items[index++];
        action(item);
        Sprite2D* ptr = item->FirstChild;
        while (ptr) {
            IterateBag.Add(ptr);
            ptr = ptr->Next;
        }
    }
}

void Sprite2D::SetInStage()
{
    if ((Flags & IN_STAGE) != 0) return;
    Flags |= IN_STAGE;
    MarkContentInvalid();
    Sprite2D* ptr = FirstChild;
    while (ptr)
    {
        ptr->SetInStage();
        ptr = ptr->Next;
    }

    if (_Parent == Stage2D::I)
        InvalidateContent();

    Init();
    //OnInit?.Invoke(this);
}


Stage2D* Stage2D::I = nullptr;

}
