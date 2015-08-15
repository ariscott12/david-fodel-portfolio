<?php
/**
 * This file is a good place to preprocess any custom theme components you create.
 */
function minim_preprocess_field_image_banner(&$v) {
  if (!empty($v['file'])) {
    $file = file_load($v['file']);
    $v['image'] = theme('image', array('path' => $file->uri));
  }
}
