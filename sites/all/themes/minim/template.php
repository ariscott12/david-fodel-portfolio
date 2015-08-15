<?php
/**
 * Theme includes
 */
$theme_path = drupal_get_path('theme', 'minim');
require_once($theme_path . '/includes/base.inc');
require_once($theme_path . '/includes/views.inc');
require_once($theme_path . '/includes/components.inc');

function minim_theme($existing, $type, $theme, $path) {
  return array(
    'field_image_banner' => array(
      'template' => 'field_image_banner',
      'path' => $path . '/templates/components',
      'variables' => array('file' => FALSE, 'text' => '')
    )
  );
}
