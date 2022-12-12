var files = <?php $out = array();
foreach (glob('Fbx/*.fbx') as $filename) {
    $p = pathinfo($filename);
    $out[] = $p['filename'];
}
echo json_encode($out); ?>;