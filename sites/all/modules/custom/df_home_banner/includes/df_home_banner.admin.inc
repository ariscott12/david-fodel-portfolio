<?php

function df_home_banner_form($form, $form_state) {
  $form = array();
  $form['home_page_banner_text'] = array(
    '#title' => t('Front Page Banner Text'),
    '#type' => 'textfield',
    '#default_value' => variable_get('home_page_banner_text', ''),
  );
  $form['home_page_banner_path'] = array(
    '#title' => t('Front Page Banner File'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('home_page_banner_path', ''),
    '#upload_location' => 'public://front_page_banner/',
    '#required' => TRUE
  );
  $form['#submit'][] = 'df_home_banner_form_submit';
  return system_settings_form($form);
}

function df_home_banner_form_submit($form, $form_state) {
  $file = file_load($form_state['values']['home_page_banner_path']);
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);
  global $user;
  file_usage_add($file, 'df_home_banner', 'df_home_banner', $user->uid);  
}
