void eve_draw() {

TEveManager::Create();
TGeoManager* geometry = TGeoManager::Import("geometry_sculpt/pionDetectorSystem.gdml");
TGeoNode* node = gGeoManager->GetTopNode();
TEveGeoTopNode* en = new TEveGeoTopNode(gGeoManager, node);
gEve->AddGlobalElement(en);
gEve->Redraw3D(kTRUE);

}
